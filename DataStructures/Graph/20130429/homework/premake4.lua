file = {
	"No_14",
	"No_15",
	"No_19",
	"No_20",
	"No_28",
	"No_31"
}

solution "CPP"

	kind "ConsoleApp"
	language "C++"
	configurations { "release" }

	location("./")
	targetextension(".out")
	targetdir(".")
	objdir("./obj/" .. os.get() .. "/")

	flags { "EnableSSE", "EnableSSE2", "ExtraWarnings" }
	buildoptions {
		"-std=c++11",
		"-m64",
		"-O2",
	}

	function create_project(val)
		project(val)
			files { val..".cpp" }
			targetname(val)
	end

	local files = file
	for iter, value in pairs(files) do
		create_project(value)
	end

