#include <phragics/dep/std/container/map.hpp>

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct ClassMember {
	std::string type;
	std::string name;
};

struct Class {
	std::string name;
	std::vector<ClassMember> members;
};

struct ClassFormatter {
	virtual auto formatted(const Class& c) -> std::string = 0;
};

struct CppClassFormatter : ClassFormatter {
	auto formatted(const Class& c) -> std::string override {
		auto str = std::stringstream();
		str << "struct " << c.name << " {\n";
		for(auto& member : c.members) {
			str << "\t" << member.type << " " << member.name << ";\n";
		}
		str << "};\n";
		return str.str();
	}
};

struct GlslClassFormatter : ClassFormatter {
	auto formatted(const Class& c) -> std::string override {
		auto str = std::stringstream();
		str << "struct " << c.name << " {\n";
		for(auto& member : c.members) {
			str << "\t"  << member.type << " " << member.name << ";\n";
		}
		str << "};\n";
		return str.str();
	}
};

struct GraphicsPipelineIn {
	std::string granularity;
	std::string type;
	std::string name;
};

struct GraphicsPipelineData {
	std::string type;
	std::string name;
};

struct GraphicsPipelineKernel {
	std::string name;
	std::vector<GraphicsPipelineData> inputs;
	std::vector<GraphicsPipelineData> outputs;
	std::string body;
};

auto vertexTransformer() -> GraphicsPipelineKernel {
	auto kernel = GraphicsPipelineKernel();
	kernel.name = "transform_vertex";

	return kernel;
}

struct GraphicsPipelineStage {
	std::string name;
	std::map<std::string, GraphicsPipelineStage> stages;
};

struct GraphicsPipeline {
	std::vector<GraphicsPipelineIn> inputs;
	std::map<std::string, GraphicsPipelineStage> stages;
};

struct OpenglGraphicsPipelineBuilder {
	auto build(const GraphicsPipeline& gp) -> std::string {
		auto ss = std::stringstream();
		if(auto vs = phragics::std_::findPtr())
		return ss.str();
	}

	auto buildFragmentShader(const GraphicsPipeline& gp) -> std::string {
		auto ss = std::stringstream();
		ss << "// Fragment shader\n";
		return ss.str();
	}

	auto buildVertexShader(const GraphicsPipeline& gp) -> std::string {
		auto ss = std::stringstream();
		ss << "// Vertex shader\n";
		return ss.str();
	}
};

int main() {
	auto c = Class();
	c.name = "Camera";
	{
		auto& m = c.members.emplace_back();
		m.name = "MVP";
		m.type = "mat4";
	}

	auto cppFormatter = CppClassFormatter();
	std::cout << cppFormatter.formatted(c);
}
