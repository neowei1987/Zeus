##********************just care what we should care(not for gmake fans)*******************************#

##eg:*************************************************************************************************#
# [root@bash]# gmake -f ../export/home/../home/make/so.version.demo.new/makefile output_path=/tmp/project1/bin output_separate=0 debug=1 trace=1
#
# only compile and force recompile two module:"lib1/foo, app" with order defiend by $(module) that means compile "lib1/foo" first and "app" second
# [root@bash]# gmake -f ../../make/so.version.demo.new/makefile module="lib1/foo app" recompile=1
##****************************************************************************************************#

##color prompt****************************************************************************************#
# if we use "my_gmake" file as syntax file and vibrantint as color scheme which are attached with this gmk_library, we will see three kinds of color
# which we should care
# red: we should particularly notice it, which we almost change everytimes.
# blue: we also need to change it if it's necessary, but it isn't so frequent as red color as
# green: maybe we want to define these varibles by ourselves although it is not necessary in most time. It can work by itself without our care
##****************************************************************************************************#

##variable define style prompt:***********************************************************************#
# 1. all uppercase: means that it's operation data, whose value user usually change but we should distinguish MAKE variable from it 
#
# 2. all lowercase: means that it's used by inner gmk_include library, generic speaking user will not care about it
# 3. all uppercast and start with "E_" means that it's a Environment varible
##****************************************************************************************************#

##we should specially care about these variables******************************************************#
					# set modules compiled in order
# 2010-01-06 will compile only module defined by MODULE_ONLY_COMPILE which exclude variable:MODULE_COMPILE_ORDER, MODULE_NO_COMPILE	
MODULE_ONLY_COMPILE 	:=# server.order.create/svr.so# server.order.create/spp.so server.order.create/svr.so#tools/orm# src.sdk
# 2009-05-16 if module need be compiled in some order, use this param to define order. it will compile all module except module defined in_no_compile
MODULE_COMPILE_ORDER	:= ./ #:=0 will not compile any module, := will compile all of module in $(solution_path)
# 2009-05-14 remove module that need not be compiled
# 2009-11-07 if MODULE_NO_COMPILE contains "./" that means will not compile the file in $(APP_APTH) but module(sub directory)
MODULE_NO_COMPILE		:= #tools/orm# base/dao# library bk# foo app

					# set compiling dependence
# same as $C_INCLUDE_PATH $CPP_INCLUDE_PATH or gcc -I option. it will not be covered by $(INCLUDE_PATH_MODULE) unless $(INCLUDE_PATH_MODULE) start with 0
# we should not use ":=" but "=" because we usually use variable $(solution_path) defined in gmk_library which hasn't been evaluated now
INCLUDE_PATH			= #$(solution_path)/base/library/include $(solution_path)/base/include $(solution_path)/base/dao/generate #base/comm/ttc_engine# /usr/local/service/mysql-5.0.26/include#base/comm base/include base/comm/log base/library/include

# default library path where we will find supporting static library in when make static library
LINK_PATH_S             :=
# default library name list which we need to find when make static library
LINK_LIB_S              :=

# default library path where we will find supporting static or dynamic library in when link. It will not be covered by $(LINK_PATH_MODULE) unless $(LINK_PATH_MODULE) start with 0
# we should not use ":=" but "=" because we usually use variable $(binary_path) defined in gmk_library which hasn't been evaluated now 
LINK_PATH				= #$(solution_path)/base/lib64 /lib64 /usr/lib64 /usr/local/lib64# /lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu# /usr/local/lib /usr/lib# /export/home/apue/apue10/10-6/bin# $(binary_path) # /usr/lib32# /export/home/apue/Common/apue.2e/lib# $(binary_path)/foo 
# default library name list which we need to find when link. It will not be covered by $(LINK_LIB_MODULE) unless $(LINK_LIB_MODULE) start with 0
LINK_LIB				:= -lstdc++ #-lspp -lqos_client -lttc -lmsglog -ldnscli -lmysqlclient -liconv -lpcre -lrt -lpthread -ldl -ltinyxml
# -lstdc++#../../../../opt/gcc/gcc-4.4.3/lib/libstdc++.so#/opt/gcc/gcc-4.4.3/lib/libstdc++.so # -lrt#-lSleep2#-lposix4# -lrt#-ldl -lcppunit#-R. -lSleep2# -lapue#-lfoo#-Wl,-Mapp/mapfile -R. -lfoo

					# set compiling flags
# default compile option. it will be covered by $(USER_CFLAGS_MODULE) unless $(USER_CFLAGS_MODULE) is null
USER_CFLAGS				:=-m64 -Wall -fPIC -D_GNU_SOURCE -D_REENTRANT -D_OS_LINUX_ -D_COMPILER_CUR_=_COMPILER_GNU_GCC_4_4_3_ -D_NO_COMPILE_POLICY_MESSAGE_# -D_REFUND_FAKE_#-O2 -DNDEBUG# -D_COMPILER_CUR_=_COMPILER_GNU_GCC_3_4_6_ -D_OS_LINUX_# -D_TRACE_RUSH_INDEPENDENT_#-Wno-deprecated# --with-low-memory -fno-inline# 0 -std=c99
# default so link option. it will be covered by $(USER_SOFLAGS_MODULE) unless $(USER_SOFLAGS_MODULE) is null
USER_SOFLAGS			:=-m64 --export-dynamic -Bdynamic# ../../Base/Comm/md5c.o ../../Base/Comm/log/clog.o#../../Base/Comm/md5c.o# -fPIC# 0 -shared# -mimpure-text	
# default app link option. it will be covered by $(USER_APP_MODULE) unless $(USER_APPFLAGS_MODULE) is null
USER_APP_FLAGS			:=-m64 -Bdynamic# -rdynamic# ../../Base/Comm/md5c.o

PUBLISH_PATH			:= #~/server_test/spp_fw_sync/lib
#PUBLISH_PATH			:=/data/sangechen/spp/spp_fw_order_create/lib
##****************************************************************************************************#


##set sub folder and other folder to compile**********************************************************#
# can use relative path because use $(MAKEFILE_LIST) to get current module.gmk's path in func get-src-files and extend-sub-src
# func "get-src-files" with add current module.gmk's path for each file in "subdir_no_compile" because $4 is "1"
#      when Call $$(eval $$(call extend-dir,$$(subdirectory),$$(SUB_PATH_NO_COMPILE),$$(subdir_recursive),1)) in "make-src"

#whether subdir will be recursive compiled in same module that has a "module.gmk" or "makefile".It'll be inherited by "SUB_PATH_RECURSIVE_MODULE" defined in "module.gmk"
SUB_PATH_RECURSIVE		:=1
#filter subdir or files that will not be compiled in same module.It'll be inherited by "SUB_PATH_NO_COMPILE_MODULE" defined in "module.gmk"
SUB_PATH_NO_COMPILE		:=#src/librar%/# test.c tmp/test.c#te%.c tmp/test.c tmp/tes%.c tmp1/% tmp2%/

OTHER_PATH1				=#$(solution_path)/../../Base/Comm# $(solution_path)/other.dir#/export/home/make/so.version.demo.new/other.dir
OTHER_PATH2				=#$(solution_path)/../dao#$(solution_path)/other.dir.1#/export/home/make/so.version.demo.new/other.dir.1
#some others dirs that is not belongs $(solution_path) will be compiled in same module that has a "module.gmk" or "makefile".It'll be inherited by "OTHER_PATH_MODULE" defined in "module.gmk"
OTHER_PATH				=#$(solution_path)/base/platform #$(solution_path)/base/library 
#whether others dirs will be recursive compiled in same module. It'll be inherited by "OTHER_PATH_RECURSIVE_MODULE" defined in "module.gmk"
OTHER_PATH_RECURSIVE	=1
#filter subdir or files in other dir that will not be compiled in same module.It'll be inherited by "OTHER_PATH_NO_COMPILE_MODULE" defined in "module.gmk"
OTHER_PATH_NO_COMPILE	=#$(solution_path)/base/business/logic/COrde%.cpp $(solution_path)/base/business/logic/CT%.cpp $(solution_path)/base/dao/wrapper/groupon.item.main.cpp# $(solution_path)/server.order.create/src/CTask.Icson.cpp #$(OTHER_PATH1)/%.cpp $(OTHER_PATH1)/log/%.cpp $(OTHER_PATH1)/dao/%.cpp#$(OTHER_PATH1)/other.test.c $(OTHER_PATH1)/tmp4/other.tmp4.test2.c $(OTHER_PATH2)/tmp4/other1.tmp4.test1.c

OTHER_COMPILE_FILE		=

##****************************************************************************************************#

##maybe we want to define these varibles by ourselves although it is not necessary in most time*******#
# define default compile debug status. it will be change by command variable: debug=1
use_debug				:=0#$(if $(debug),1,0)
# choose default compiler,eg: gcc, g++, cc, CC. default:gcc
user_compiler			:=g++ #gcc443# g++

# define solution path which has makefile and many sub project in different sub folder. default path is same as makefile's which is compiling
solution_path			:=# /export/home/make/so.version.demo.new. it also can be referenced in module.gmk to purvey solation path
# define compile output path and it can be changed by command variable: output_path=. it also can be referenced in module.gmk to purvey output path
binary_path				:=# default: $(trip $(solution_path)/_bin)
#2009-10-30 if equal 1 that every sub app has own ouput path in binary_path. it can be changed by commmand variable: output_separate
binary_path_separate	:=1# default:1
#2012-02-02 if recompile when gmk file is updated
is_dependence_gmk		:=0# 1
##****************************************************************************************************#

##inner variable for gmk_liburay we will include******************************************************#
#define path of inner gmk_library which would work a lot of work for us later
#gmk_include_path		:= $(E_GMK_INCLUDE_PATH)#enviroment variable
gmk_include_path		:= $(if $(E_GMK_INCLUDE_PATH),$(E_GMK_INCLUDE_PATH),./gmk_include/)#enviroment variable
#define path of current compiled makefile so that we know the solution path if $(solution_path) is null
cur_makefile_path		:= $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
#$(warning "cur_makefile_path:"$(cur_makefile_path))
##****************************************************************************************************#

##include gmk_library which do ugly work for us now***************************************************#
include $(gmk_include_path)/Nonrecursive/nonrecursive.ex.gmk

##****************************************************************************************************#
# we can do sth else in this target after compile finished
# must under include nonrecursive.ex.gmk or target "all" will not be default one
_root_appendix: $(shell echo "MAKEFILE[$(solution_path)]")
#	@echo "$< finished. appendix:"
