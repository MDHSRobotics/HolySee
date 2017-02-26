##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=CSee
ConfigurationName      :=Release
WorkspacePath          := "/home/ubuntu/workspace"
ProjectPath            := "/home/ubuntu/workspace/CSee"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=26/02/17
CodeLitePath           :="/home/ubuntu/.codelite"
LinkerName             :=/usr/bin/aarch64-linux-gnu-g++
SharedObjectLinkerName :=/usr/bin/aarch64-linux-gnu-g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName).so
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="CSee.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -O2
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/usr/include/gstreamer-1.0 $(IncludeSwitch)/usr/lib/aarch64-linux-gnu/gstreamer-1.0/include $(IncludeSwitch)/usr/include/glib-2.0 $(IncludeSwitch)/usr/lib/aarch64-linux-gnu/glib-2.0/include $(IncludeSwitch)/usr/include/opencv 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)opencv_calib3d $(LibrarySwitch)opencv_contrib $(LibrarySwitch)opencv_core $(LibrarySwitch)opencv_features2d $(LibrarySwitch)opencv_flann $(LibrarySwitch)opencv_gpu $(LibrarySwitch)opencv_highgui $(LibrarySwitch)opencv_imgproc $(LibrarySwitch)opencv_legacy $(LibrarySwitch)opencv_ml $(LibrarySwitch)opencv_objdetect $(LibrarySwitch)opencv_photo $(LibrarySwitch)opencv_stitching $(LibrarySwitch)opencv_superres $(LibrarySwitch)opencv_ts $(LibrarySwitch)opencv_video $(LibrarySwitch)opencv_videostab $(LibrarySwitch)opencv_detection_based_tracker $(LibrarySwitch)opencv_esm_panorama $(LibrarySwitch)opencv_facedetect $(LibrarySwitch)opencv_imuvstab $(LibrarySwitch)opencv_tegra $(LibrarySwitch)opencv_vstab $(LibrarySwitch)cufft $(LibrarySwitch)npps $(LibrarySwitch)nppi $(LibrarySwitch)nppc $(LibrarySwitch)cudart $(LibrarySwitch)atomic $(LibrarySwitch)tbb $(LibrarySwitch)rt $(LibrarySwitch)pthread $(LibrarySwitch)m $(LibrarySwitch)dl $(LibrarySwitch)gstreamer-1.0 $(LibrarySwitch)gstbase-1.0 $(LibrarySwitch)gobject-2.0 $(LibrarySwitch)glib-2.0 
ArLibs                 :=  "opencv_calib3d" "opencv_contrib" "opencv_core" "opencv_features2d" "opencv_flann" "opencv_gpu" "opencv_highgui" "opencv_imgproc" "opencv_legacy" "opencv_ml" "opencv_objdetect" "opencv_photo" "opencv_stitching" "opencv_superres" "opencv_ts" "opencv_video" "opencv_videostab" "opencv_detection_based_tracker" "opencv_esm_panorama" "opencv_facedetect" "opencv_imuvstab" "opencv_tegra" "opencv_vstab" "cufft" "npps" "nppi" "nppc" "cudart" "atomic" "tbb" "rt" "pthread" "m" "dl" "gstreamer-1.0" "gstbase-1.0" "gobject-2.0" "glib-2.0" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/local/cuda-8.0/lib64 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/aarch64-linux-gnu-ar rcu
CXX      := /usr/bin/aarch64-linux-gnu-g++
CC       := /usr/bin/aarch64-linux-gnu-gcc
CXXFLAGS :=  -O2 -std=c++11 -fPIC -pthread $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/aarch64-linux-gnu-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/CircleAR.cpp$(ObjectSuffix) $(IntermediateDirectory)/Filter.cpp$(ObjectSuffix) $(IntermediateDirectory)/FilterManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/GearAR.cpp$(ObjectSuffix) $(IntermediateDirectory)/gstarfilter.cpp$(ObjectSuffix) $(IntermediateDirectory)/SquareAR.cpp$(ObjectSuffix) $(IntermediateDirectory)/SteamAR.cpp$(ObjectSuffix) $(IntermediateDirectory)/gstlidarimg.cpp$(ObjectSuffix) $(IntermediateDirectory)/gstlidarsrc.cpp$(ObjectSuffix) $(IntermediateDirectory)/LidarDevice.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/csee.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)
	@$(MakeDirCommand) "/home/ubuntu/workspace/.build-release"
	@echo rebuilt > "/home/ubuntu/workspace/.build-release/CSee"

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/CircleAR.cpp$(ObjectSuffix): CircleAR.cpp $(IntermediateDirectory)/CircleAR.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/CSee/CircleAR.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CircleAR.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CircleAR.cpp$(DependSuffix): CircleAR.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CircleAR.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CircleAR.cpp$(DependSuffix) -MM "CircleAR.cpp"

$(IntermediateDirectory)/CircleAR.cpp$(PreprocessSuffix): CircleAR.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CircleAR.cpp$(PreprocessSuffix) "CircleAR.cpp"

$(IntermediateDirectory)/Filter.cpp$(ObjectSuffix): Filter.cpp $(IntermediateDirectory)/Filter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/CSee/Filter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Filter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Filter.cpp$(DependSuffix): Filter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Filter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Filter.cpp$(DependSuffix) -MM "Filter.cpp"

$(IntermediateDirectory)/Filter.cpp$(PreprocessSuffix): Filter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Filter.cpp$(PreprocessSuffix) "Filter.cpp"

$(IntermediateDirectory)/FilterManager.cpp$(ObjectSuffix): FilterManager.cpp $(IntermediateDirectory)/FilterManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/CSee/FilterManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FilterManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FilterManager.cpp$(DependSuffix): FilterManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FilterManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FilterManager.cpp$(DependSuffix) -MM "FilterManager.cpp"

$(IntermediateDirectory)/FilterManager.cpp$(PreprocessSuffix): FilterManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FilterManager.cpp$(PreprocessSuffix) "FilterManager.cpp"

$(IntermediateDirectory)/GearAR.cpp$(ObjectSuffix): GearAR.cpp $(IntermediateDirectory)/GearAR.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/CSee/GearAR.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GearAR.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GearAR.cpp$(DependSuffix): GearAR.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GearAR.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GearAR.cpp$(DependSuffix) -MM "GearAR.cpp"

$(IntermediateDirectory)/GearAR.cpp$(PreprocessSuffix): GearAR.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GearAR.cpp$(PreprocessSuffix) "GearAR.cpp"

$(IntermediateDirectory)/gstarfilter.cpp$(ObjectSuffix): gstarfilter.cpp $(IntermediateDirectory)/gstarfilter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/CSee/gstarfilter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gstarfilter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gstarfilter.cpp$(DependSuffix): gstarfilter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gstarfilter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/gstarfilter.cpp$(DependSuffix) -MM "gstarfilter.cpp"

$(IntermediateDirectory)/gstarfilter.cpp$(PreprocessSuffix): gstarfilter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gstarfilter.cpp$(PreprocessSuffix) "gstarfilter.cpp"

$(IntermediateDirectory)/SquareAR.cpp$(ObjectSuffix): SquareAR.cpp $(IntermediateDirectory)/SquareAR.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/CSee/SquareAR.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SquareAR.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SquareAR.cpp$(DependSuffix): SquareAR.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SquareAR.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SquareAR.cpp$(DependSuffix) -MM "SquareAR.cpp"

$(IntermediateDirectory)/SquareAR.cpp$(PreprocessSuffix): SquareAR.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SquareAR.cpp$(PreprocessSuffix) "SquareAR.cpp"

$(IntermediateDirectory)/SteamAR.cpp$(ObjectSuffix): SteamAR.cpp $(IntermediateDirectory)/SteamAR.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/CSee/SteamAR.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SteamAR.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SteamAR.cpp$(DependSuffix): SteamAR.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SteamAR.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SteamAR.cpp$(DependSuffix) -MM "SteamAR.cpp"

$(IntermediateDirectory)/SteamAR.cpp$(PreprocessSuffix): SteamAR.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SteamAR.cpp$(PreprocessSuffix) "SteamAR.cpp"

$(IntermediateDirectory)/gstlidarimg.cpp$(ObjectSuffix): gstlidarimg.cpp $(IntermediateDirectory)/gstlidarimg.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/CSee/gstlidarimg.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gstlidarimg.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gstlidarimg.cpp$(DependSuffix): gstlidarimg.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gstlidarimg.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/gstlidarimg.cpp$(DependSuffix) -MM "gstlidarimg.cpp"

$(IntermediateDirectory)/gstlidarimg.cpp$(PreprocessSuffix): gstlidarimg.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gstlidarimg.cpp$(PreprocessSuffix) "gstlidarimg.cpp"

$(IntermediateDirectory)/gstlidarsrc.cpp$(ObjectSuffix): gstlidarsrc.cpp $(IntermediateDirectory)/gstlidarsrc.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/CSee/gstlidarsrc.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gstlidarsrc.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gstlidarsrc.cpp$(DependSuffix): gstlidarsrc.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gstlidarsrc.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/gstlidarsrc.cpp$(DependSuffix) -MM "gstlidarsrc.cpp"

$(IntermediateDirectory)/gstlidarsrc.cpp$(PreprocessSuffix): gstlidarsrc.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gstlidarsrc.cpp$(PreprocessSuffix) "gstlidarsrc.cpp"

$(IntermediateDirectory)/LidarDevice.cpp$(ObjectSuffix): LidarDevice.cpp $(IntermediateDirectory)/LidarDevice.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/CSee/LidarDevice.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/LidarDevice.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/LidarDevice.cpp$(DependSuffix): LidarDevice.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/LidarDevice.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/LidarDevice.cpp$(DependSuffix) -MM "LidarDevice.cpp"

$(IntermediateDirectory)/LidarDevice.cpp$(PreprocessSuffix): LidarDevice.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/LidarDevice.cpp$(PreprocessSuffix) "LidarDevice.cpp"

$(IntermediateDirectory)/csee.cpp$(ObjectSuffix): csee.cpp $(IntermediateDirectory)/csee.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/CSee/csee.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/csee.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/csee.cpp$(DependSuffix): csee.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/csee.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/csee.cpp$(DependSuffix) -MM "csee.cpp"

$(IntermediateDirectory)/csee.cpp$(PreprocessSuffix): csee.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/csee.cpp$(PreprocessSuffix) "csee.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


