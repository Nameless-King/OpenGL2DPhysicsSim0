cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(OpenGLPhysics0)

add_executable(
	Program
	Main.cpp
	Window.cpp
	Shader.cpp
	./Dependencies/stb_image.cpp
	Texture.cpp
	VertexArrayObj.cpp
	VertexBufferObj.cpp
	IndexBufferObj.cpp
	Object.cpp
	Particle.cpp
	./Dependencies/imgui/imgui.cpp
	./Dependencies/imgui/imgui_impl_glfw.cpp
	./Dependencies/imgui/imgui_impl_opengl3.cpp
	./Dependencies/imgui/imgui_draw.cpp
	./Dependencies/imgui/imgui_demo.cpp
	./Dependencies/imgui/imgui_widgets.cpp
	Renderer.cpp
	StaticRenderer.cpp
	SceneManager.cpp
	Hitbox.cpp
	OBB.cpp
	Physics2D.cpp
	EngineMaths.cpp
	RigidBody2D.cpp
	SceneRestingContact.cpp
	SceneIntegrator.cpp
	SceneForces.cpp
	SceneParticle.cpp
	SceneForceGenerator.cpp
	SceneBuoyantForce.cpp
	SceneCollisions.cpp
	ScenePhysicsSystem.cpp
	SceneCollisionDetection.cpp
	ForceDrag.cpp
	ForceGravity.cpp
	ForceRegistry.cpp
	ForceSpring.cpp
	ForceAnchoredSpring.cpp
	ForceBungee.cpp
	ForceBuoyancy.cpp
	ForceFakeSpring.cpp
	ObjectContact.cpp
	CameraController.cpp
	CollisionBatchResolver.cpp
	Experimental.cpp
	#TODO: include other source files
)

target_include_directories(Program PRIVATE "C:\\Program Files\\mingw-w64\\x86_64-8.1.0-posix-seh-rt_v6-rev0\\mingw64\\x86_64-w64-mingw32\\include")

target_link_libraries(Program
	glew32
	glfw3dll
	opengl32
)
