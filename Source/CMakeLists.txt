cmake_minimum_required(VERSION 3.20.0)

project(GAML-C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_SUPPRESS_REGENERATION true)



include_directories(${PROJECT_SOURCE_DIR}/gaml-c/Core)
include_directories(${PROJECT_SOURCE_DIR}/gaml-c/Backend)
include_directories(${PROJECT_SOURCE_DIR}/gaml-c/Frontend)
include_directories(${PROJECT_SOURCE_DIR}/gaml-c/Middleware)
include_directories(${PROJECT_SOURCE_DIR}/gaml-c/ToolChain)

file(GLOB_RECURSE Sources 
"${PROJECT_SOURCE_DIR}/gaml-c/*.h" "${PROJECT_SOURCE_DIR}/gaml-c/*.cpp"
"${PROJECT_SOURCE_DIR}/ThirdParty/*.h" "${PROJECT_SOURCE_DIR}/ThirdParty/*.cpp"
)

if( NOT UNIX )
    include_directories(${PROJECT_SOURCE_DIR}/ThirdParty/llvm/Windows/include)
    file(GLOB LLVMLibs "${PROJECT_SOURCE_DIR}/ThirdParty/llvm/Windows/lib/*.lib")
else()
    #TODO
endif( NOT UNIX )


macro(GroupSources curdir)
	file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}	${PROJECT_SOURCE_DIR}/${curdir}/*)
	foreach(child ${children})
		if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			GroupSources(${curdir}/${child})
		else()
			string(REPLACE "/" "\\" groupname ${curdir})
			string(REPLACE "src" "Common" groupname ${groupname})
			source_group(${groupname} FILES	${PROJECT_SOURCE_DIR}/${curdir}/${child})
		endif()
	endforeach()
endmacro()
   
GroupSources(gaml-c)
GroupSources(ThirdParty)



add_executable(gaml-c ${Sources})

target_link_libraries(gaml-c ${LLVMLibs})



 

