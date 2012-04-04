cmake_minimum_required(VERSION 2.6) # Pour éviter un warning au lancement de CMake, on doit préciser la version minimale

# Nom du projet
project(PTZ_openCV)

include_directories(
	./dep/include/opencv2
	./dep/include/opencv
	./dep/include/
	./dep/include/libimg
)

link_directories(
	../dep/lib
	/usr/lib
)

find_package (Threads)

SET(EXECUTABLE_OUTPUT_PATH ../bin/)
#SET(CMAKE_CXX_FLAGS -D_REENTRANT)
#SET(CMAKE_C_FLAGS -D_REENTRANT)


file(
    GLOB_RECURSE
    source_files
    src/*
)

# Déclaration de l'exécutable
add_executable(
    PTZ_ICOND
    ${source_files}
)

target_link_libraries(
        PTZ_ICOND
#libs de libPF
	colorutils
	stringutils
	bspline
	timeutils
	imageutils
	colsegmentation
	imgproducer
	gaussian
	motiondistr
	2ddetector
	likelihood
	prior
	dynamics
	targets
	shapedescr
	filters
	misc
#libs de OpenCV
	opencv_core
	opencv_highgui
	opencv_imgproc
	opencv_video
#libs de curl
	curl
	${CMAKE_THREAD_LIBS_INIT}
)


