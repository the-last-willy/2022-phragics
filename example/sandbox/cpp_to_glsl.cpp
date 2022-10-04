#include "piecewise/common/numeric/rounding.hpp"

#include <cstring>
#include <iostream>
#include <variant>
#include <vector>

template<typename T>
using NP = T*;

template<typename T>
using NullTerminated = NP<T>;

//

template<typename T>
using BasicMachineUnit = T;

//

auto aligned_offset(
	BasicMachineUnit<int> base_offset,
	BasicMachineUnit<int> base_alignment)
-> BasicMachineUnit<int>
{
	return pcws::ceiled(base_offset, base_alignment);
}

//

struct UndefinedType {
	NullTerminated<const char> name = "";
};

struct VoidType {
	NullTerminated<const char> name = "void";
};

struct ScalarType {
	NullTerminated<const char> name = "";
	BasicMachineUnit<int> size = 1;
};

auto base_alignment(ScalarType i) -> BasicMachineUnit<int> {
	// OpenGL 4.6 specifications / 7.6.2.2 / 1
	return i.size;
}

struct VectorType {
	NullTerminated<const char> name = "";
	ScalarType scalar_type;
	int component_count = 0;
};

auto scalar_type(const VectorType& v) -> const ScalarType& {
	return v.scalar_type;
}

auto base_alignment(VectorType i) -> BasicMachineUnit<int> {
	auto n = base_alignment(i.scalar_type);
	if(i.component_count == 2) {
		// OpenGL 4.6 specifications / 7.6.2.2 / 2
		return 2 * n;
	} else if(i.component_count == 3) {
		// OpenGL 4.6 specifications / 7.6.2.2 / 3
		return 4 * n;
	} else if(i.component_count == 4) {
		// OpenGL 4.6 specifications / 7.6.2.2 / 2
		return 4 * n;
	} else {
		return 0;
	}
}

struct Type {
	std::variant<UndefinedType, ScalarType, VectorType> details;
};

auto base_alignment(const Type& t) -> BasicMachineUnit<int> {
	if(auto s = get_if<ScalarType>(&t.details)) {
		return base_alignment(*s);
	} else if(auto v = get_if<VectorType>(&t.details)) {
		return base_alignment(*v);
	} else {
		return 0;
	}
}

auto name(const Type& t) -> NullTerminated<const char> {
	return std::visit([](auto& a) { return a.name; }, t.details);
}

auto size(const Type& t) -> BasicMachineUnit<int> {
	if(auto s = get_if<ScalarType>(&t.details)) {
		return s->size;
	} else if(auto v = get_if<VectorType>(&t.details)) {
		return v->component_count * v->scalar_type.size;
	} else {
		return 0;
	}
}

struct StructureMember {
	Type type;
	std::string name;

	BasicMachineUnit<int> aligned_offset;
};

struct Structure {
	NullTerminated<const char> name;
	std::vector<StructureMember> members;

	BasicMachineUnit<int> base_alignment;
	BasicMachineUnit<int> size;
};

void compute_std140_memory_layout(Structure& s) {
	s.base_alignment = 1;
	s.size = 0;
	auto offset = 0;
	for(auto i = 0u; i < size(s.members); ++i) {
		auto m = &s.members[i];
		auto ba = base_alignment(m->type);
		s.base_alignment = std::max(s.base_alignment, ba);
		offset = pcws::ceiled(offset, ba);
		m->aligned_offset = offset;
		offset += size(m->type);
	}
	s.size = pcws::ceiled(offset, s.base_alignment);
}

void print_memory_layout(const Structure& s) {
	std::cout
	<< s.name
	<< ": size=" << s.size
	<< ", base_align=" << s.base_alignment
	<< std::endl;
	for(auto& m : s.members) {
		std::cout
		<< "  " << name(m.type)
		<< " " << m.name
		<< ": size=" << size(m.type)
		<< ", base_align=" << base_alignment(m.type)
		<< ", align_offset=" << m.aligned_offset
		<< std::endl;
	}
}

struct GlslFormatter {
	std::ostream* stream = &std::cout;
};

void format(GlslFormatter& f, const Structure& s) {
	*f.stream
		<< "struct " <<  s.name
		<< " {\n";
	for(auto i = 0u; i < size(s.members); ++i) {
		auto m = &s.members[i];
		*f.stream
			<< "    " << name(m->type)
			<< " " << m->name
			<< ";\n";
	}
	*f.stream<< "};\n";
}

struct CppFormatter {
	std::ostream* stream = &std::cout;
};

void format(CppFormatter& f, const Structure& s) {
	auto last_offset = BasicMachineUnit<int>(0);
	auto padding = 0;
	*f.stream
		<< "struct " <<  s.name
		<< " {\n";
	for(auto i = 0u; i < size(s.members); ++i) {
		auto m = &s.members[i];
		if(i > 0 && m->aligned_offset != last_offset) {
			*f.stream <<
				"    char padding" << padding <<
			   	"[" << m->aligned_offset - last_offset <<
			   	"];\n";
			padding += 1;
		}
		*f.stream
			<< "    " << name(m->type)
			<< " " << m->name
			<< ";\n";
		last_offset = m->aligned_offset + size(m->type);
	}
	*f.stream<< "};\n";
}

//

auto main() -> int {
	auto float_type = ScalarType{.name = "float", .size = 4};

	auto vec2_type = VectorType{.name = "vec2", .scalar_type = float_type, .component_count = 2};
//	auto vec3_type = VectorType{.name = "vec3", .scalar_type = &float_type, .component_count = 3};
	auto vec4_type = VectorType{.name = "vec4", .scalar_type = float_type, .component_count = 4};

	auto s = Structure();
	s.name = "Test";
	{
		auto m = StructureMember();
		m.name = "c";
		m.type = Type{vec2_type};
		s.members.push_back(m);
	}
	{
		auto m = StructureMember();
		m.name = "a";
		m.type = Type{float_type};
		s.members.push_back(m);
	}
	{
		auto m = StructureMember();
		m.name = "d";
		m.type = Type{vec4_type};
		s.members.push_back(m);
	}

	compute_std140_memory_layout(s);
	print_memory_layout(s);

	auto glsl_formatter = GlslFormatter();
	format(glsl_formatter, s);
	auto cpp_formatter = CppFormatter();
	format(cpp_formatter, s);
}
