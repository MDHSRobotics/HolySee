##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=MSee
ConfigurationName      :=Release
WorkspacePath          := "/home/ubuntu/workspace"
ProjectPath            := "/home/ubuntu/workspace/MSee"
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="MSee.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/usr/include/gstreamer-1.0 $(IncludeSwitch)/usr/lib/aarch64-linux-gnu/gstreamer-1.0/include $(IncludeSwitch)/usr/include/glib-2.0 $(IncludeSwitch)/usr/lib/aarch64-linux-gnu/glib-2.0/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)opencv_calib3d $(LibrarySwitch)opencv_contrib $(LibrarySwitch)opencv_core $(LibrarySwitch)opencv_features2d $(LibrarySwitch)opencv_flann $(LibrarySwitch)opencv_gpu $(LibrarySwitch)opencv_highgui $(LibrarySwitch)opencv_imgproc $(LibrarySwitch)opencv_legacy $(LibrarySwitch)opencv_ml $(LibrarySwitch)opencv_objdetect $(LibrarySwitch)opencv_photo $(LibrarySwitch)opencv_stitching $(LibrarySwitch)opencv_superres $(LibrarySwitch)opencv_ts $(LibrarySwitch)opencv_video $(LibrarySwitch)opencv_videostab $(LibrarySwitch)opencv_detection_based_tracker $(LibrarySwitch)opencv_esm_panorama $(LibrarySwitch)opencv_facedetect $(LibrarySwitch)opencv_imuvstab $(LibrarySwitch)opencv_tegra $(LibrarySwitch)opencv_vstab $(LibrarySwitch)cufft $(LibrarySwitch)npps $(LibrarySwitch)nppi $(LibrarySwitch)nppc $(LibrarySwitch)cudart $(LibrarySwitch)atomic $(LibrarySwitch)tbb $(LibrarySwitch)rt $(LibrarySwitch)pthread $(LibrarySwitch)m $(LibrarySwitch)dl $(LibrarySwitch)gstreamer-1.0 $(LibrarySwitch)gobject-2.0 $(LibrarySwitch)glib-2.0 $(LibrarySwitch)PocoFoundation $(LibrarySwitch)PocoUtil $(LibrarySwitch)pthread 
ArLibs                 :=  "opencv_calib3d" "opencv_contrib" "opencv_core" "opencv_features2d" "opencv_flann" "opencv_gpu" "opencv_highgui" "opencv_imgproc" "opencv_legacy" "opencv_ml" "opencv_objdetect" "opencv_photo" "opencv_stitching" "opencv_superres" "opencv_ts" "opencv_video" "opencv_videostab" "opencv_detection_based_tracker" "opencv_esm_panorama" "opencv_facedetect" "opencv_imuvstab" "opencv_tegra" "opencv_vstab" "cufft" "npps" "nppi" "nppc" "cudart" "atomic" "tbb" "rt" "pthread" "m" "dl" "gstreamer-1.0" "gobject-2.0" "glib-2.0" "PocoFoundation" "PocoUtil" "pthread" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/local/cuda-8.0/lib64 $(LibraryPathSwitch)/usr/local/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/aarch64-linux-gnu-ar rcu
CXX      := /usr/bin/aarch64-linux-gnu-g++
CC       := /usr/bin/aarch64-linux-gnu-gcc
CXXFLAGS :=  -O2 -std=c++11 -pthread $(Preprocessors)
CFLAGS   :=  -O2 $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/aarch64-linux-gnu-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Config.cpp$(ObjectSuffix) $(IntermediateDirectory)/DNSSDBrowser.cpp$(ObjectSuffix) $(IntermediateDirectory)/easywsclient.cpp$(ObjectSuffix) $(IntermediateDirectory)/LidarSource.cpp$(ObjectSuffix) $(IntermediateDirectory)/Main.cpp$(ObjectSuffix) $(IntermediateDirectory)/MSee.cpp$(ObjectSuffix) $(IntermediateDirectory)/Reading.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source.cpp$(ObjectSuffix) $(IntermediateDirectory)/Streamer.cpp$(ObjectSuffix) $(IntermediateDirectory)/VideoSource.cpp$(ObjectSuffix) \
	



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
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Config.cpp$(ObjectSuffix): Config.cpp $(IntermediateDirectory)/Config.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/MSee/Config.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Config.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Config.cpp$(DependSuffix): Config.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Config.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Config.cpp$(DependSuffix) -MM "Config.cpp"

$(IntermediateDirectory)/Config.cpp$(PreprocessSuffix): Config.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Config.cpp$(PreprocessSuffix) "Config.cpp"

$(IntermediateDirectory)/DNSSDBrowser.cpp$(ObjectSuffix): DNSSDBrowser.cpp $(IntermediateDirectory)/DNSSDBrowser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/MSee/DNSSDBrowser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DNSSDBrowser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DNSSDBrowser.cpp$(DependSuffix): DNSSDBrowser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DNSSDBrowser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DNSSDBrowser.cpp$(DependSuffix) -MM "DNSSDBrowser.cpp"

$(IntermediateDirectory)/DNSSDBrowser.cpp$(PreprocessSuffix): DNSSDBrowser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DNSSDBrowser.cpp$(PreprocessSuffix) "DNSSDBrowser.cpp"

$(IntermediateDirectory)/easywsclient.cpp$(ObjectSuffix): easywsclient.cpp $(IntermediateDirectory)/easywsclient.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/MSee/easywsclient.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/easywsclient.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/easywsclient.cpp$(DependSuffix): easywsclient.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/easywsclient.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/easywsclient.cpp$(DependSuffix) -MM "easywsclient.cpp"

$(IntermediateDirectory)/easywsclient.cpp$(PreprocessSuffix): easywsclient.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/easywsclient.cpp$(PreprocessSuffix) "easywsclient.cpp"

$(IntermediateDirectory)/LidarSource.cpp$(ObjectSuffix): LidarSource.cpp $(IntermediateDirectory)/LidarSource.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/MSee/LidarSource.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/LidarSource.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/LidarSource.cpp$(DependSuffix): LidarSource.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/LidarSource.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/LidarSource.cpp$(DependSuffix) -MM "LidarSource.cpp"

$(IntermediateDirectory)/LidarSource.cpp$(PreprocessSuffix): LidarSource.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/LidarSource.cpp$(PreprocessSuffix) "LidarSource.cpp"

$(IntermediateDirectory)/Main.cpp$(ObjectSuffix): Main.cpp $(IntermediateDirectory)/Main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/MSee/Main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Main.cpp$(DependSuffix): Main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Main.cpp$(DependSuffix) -MM "Main.cpp"

$(IntermediateDirectory)/Main.cpp$(PreprocessSuffix): Main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Main.cpp$(PreprocessSuffix) "Main.cpp"

$(IntermediateDirectory)/MSee.cpp$(ObjectSuffix): MSee.cpp $(IntermediateDirectory)/MSee.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/MSee/MSee.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MSee.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MSee.cpp$(DependSuffix): MSee.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MSee.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MSee.cpp$(DependSuffix) -MM "MSee.cpp"

$(IntermediateDirectory)/MSee.cpp$(PreprocessSuffix): MSee.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MSee.cpp$(PreprocessSuffix) "MSee.cpp"

$(IntermediateDirectory)/Reading.cpp$(ObjectSuffix): Reading.cpp $(IntermediateDirectory)/Reading.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/MSee/Reading.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Reading.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Reading.cpp$(DependSuffix): Reading.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Reading.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Reading.cpp$(DependSuffix) -MM "Reading.cpp"

$(IntermediateDirectory)/Reading.cpp$(PreprocessSuffix): Reading.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Reading.cpp$(PreprocessSuffix) "Reading.cpp"

$(IntermediateDirectory)/Source.cpp$(ObjectSuffix): Source.cpp $(IntermediateDirectory)/Source.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/MSee/Source.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source.cpp$(DependSuffix): Source.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source.cpp$(DependSuffix) -MM "Source.cpp"

$(IntermediateDirectory)/Source.cpp$(PreprocessSuffix): Source.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source.cpp$(PreprocessSuffix) "Source.cpp"

$(IntermediateDirectory)/Streamer.cpp$(ObjectSuffix): Streamer.cpp $(IntermediateDirectory)/Streamer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/MSee/Streamer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Streamer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Streamer.cpp$(DependSuffix): Streamer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Streamer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Streamer.cpp$(DependSuffix) -MM "Streamer.cpp"

$(IntermediateDirectory)/Streamer.cpp$(PreprocessSuffix): Streamer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Streamer.cpp$(PreprocessSuffix) "Streamer.cpp"

$(IntermediateDirectory)/VideoSource.cpp$(ObjectSuffix): VideoSource.cpp $(IntermediateDirectory)/VideoSource.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ubuntu/workspace/MSee/VideoSource.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/VideoSource.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/VideoSource.cpp$(DependSuffix): VideoSource.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/VideoSource.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/VideoSource.cpp$(DependSuffix) -MM "VideoSource.cpp"

$(IntermediateDirectory)/VideoSource.cpp$(PreprocessSuffix): VideoSource.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/VideoSource.cpp$(PreprocessSuffix) "VideoSource.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


