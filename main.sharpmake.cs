//using System.IO;
//using Sharpmake;



//[Generate]
//public class XtlLibrary : Project
//{
//    public XtlLibrary()
//    {
//        Name = "xtl";
//        SourceRootPath = @"[project.SharpmakeCsPath]\xtl\src";
//        RootPath = @"[project.SharpmakeCsPath]\xtl";
//        //AdditionalSourceRootPaths.Add(@"[project.SharpmakeCsPath]\XtlLibrary\Include");

//        AddTargets(new Target(
//           Platform.win64,
//           DevEnv.vs2019,
//           Optimization.Debug | Optimization.Release,
//           OutputType.Dll | OutputType.Lib));

//    }


//    [Configure]
//    public void ConfigureAll(Project.Configuration conf, Target target)
//    {
//        //conf.ProjectPath = Path.Combine("[project.SharpmakeCsPath]", "projects");
//        conf.ProjectPath = Path.Combine("[project.SharpmakeCsPath]\\Solutions\\[project.Name]");

//        conf.IncludePaths.Add(@"[project.RootPath]\include");
//        conf.IncludePrivatePaths.Add(@"[project.SourceRootPath]\src");

//        //conf.AddPrivateDependency<Engine>(target);

//        if (target.Platform == Platform.win64)
//        {
//            conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);
//            conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.CPP17);
//        }    
//    }
//}

//[Generate]
//public class XtlTest : Project
//{
//    public XtlTest()
//    {
//        Name = "Test";
//        SourceRootPath = @"[project.SharpmakeCsPath]\test\src";
//        RootPath = @"[project.SharpmakeCsPath]\test";
//        //AdditionalSourceRootPaths.Add(@"[project.SharpmakeCsPath]\XtlLibrary\Include");

//        AddTargets(new Target(
//           Platform.win64,
//           DevEnv.vs2019,
//           Optimization.Debug | Optimization.Release
//            ));

//    }


//    [Configure]
//    public void ConfigureAll(Project.Configuration conf, Target target)
//    {
//        //conf.ProjectPath = Path.Combine("[project.SharpmakeCsPath]", "projects");
//        conf.ProjectPath = Path.Combine("[project.SharpmakeCsPath]\\Solutions\\[project.Name]");

//        conf.IncludePaths.Add(@"[project.RootPath]\include");
//        conf.IncludePrivatePaths.Add(@"[project.SourceRootPath]\src");
//        conf.AddPrivateDependency<XtlLibrary>(target);
//        //conf.AddPrivateDependency<Engine>(target);

//        if (target.Platform == Platform.win64)
//        {
//            conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);
//            conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.CPP17);
//        }
//    }
//}

//[Generate]
//public class XtlSolution : Solution
//{
//    public XtlSolution()
//    {
//        Name = "XtlSolution";
//        AddTargets(new Target(
//            Platform.win64,
//            DevEnv.vs2019,
//            Optimization.Debug | Optimization.Release));
//    }

//    [Configure]
//    public void ConfigureAll(Solution.Configuration conf, Target target)
//    {
//        conf.Name = @"[target.Optimization]_[target.OutputType]";
//        conf.SolutionPath = @"[solution.SharpmakeCsPath]\Solutions";

//        // Adds the projects to the solution. Note that because the executable
//        // has a dependency to the library, Sharpmake can automatically figures
//        // out that it should add the library to the solution too, so the
//        // second line is not actually needed.
//        conf.AddProject<XtlSolution>(target);
//        conf.AddProject<XtlLibrary>(target);
//    }

//}

//public static class Main
//{
//    [Sharpmake.Main]
//    public static void SharpmakeMain(Sharpmake.Arguments arguments)
//    {
//        arguments.Generate<XtlSolution>();
//    }
//}


//using System.IO;
//using Sharpmake;

//// Both the library and the executable can share these base settings, so create
//// a base class for both projects.
//abstract class BaseLibraryProject : Project
//{
//    public BaseLibraryProject()
//    {
//        // Declares the target for which we build the project. This time we add
//        // the additional OutputType fragment, which is a prebuilt fragment
//        // that help us specify the kind of library output that we want.
//        AddTargets(new Target(
//            Platform.win32 | Platform.win64,
//            DevEnv.vs2019,
//            Optimization.Debug | Optimization.Release,
//            OutputType.Dll | OutputType.Lib));
//    }

//    [Configure]
//    public virtual void ConfigureAll(Project.Configuration conf, Target target)
//    {
//        // This is the name of the configuration. By default, it is set to
//        // [target.Optimization] (so Debug or Release), but both the debug and
//        // release configurations have both a shared and a static version so
//        // that would not create unique configuration names.
//        conf.Name = @"[target.Optimization] [target.OutputType]";

//        // Gives a unique path for the project because Visual Studio does not
//        // like shared intermediate directories.
//        conf.ProjectPath = Path.Combine("[project.SharpmakeCsPath]/generated/[project.Name]");

//        if (target.Platform == Platform.win64)
//        {
//            conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);
//            conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.CPP17);
//        }
//    }
//}


//// The library project.
//[Generate]
//class XtlLibrary : BaseLibraryProject
//{
//    public XtlLibrary()
//    {
//        Name = "xtl";
//        SourceRootPath = @"[project.SharpmakeCsPath]/xtl/src";
//        RootPath = @"[project.SharpmakeCsPath]/xtl";
//    }

//    public override void ConfigureAll(Project.Configuration conf, Target target)
//    {
//        base.ConfigureAll(conf, target);

//        // Setup the precompiled headers for the project. Just assigning a
//        // value to those fields is enough for Sharpmake to understand that
//        // the project has precompiled headers.
//        // conf.PrecompHeader = "precomp.hpp";
//        //conf.PrecompSource = "precomp.cpp";

//        // Sets the include path of the library. Those will be shared with any
//        // project that adds this one as a dependency. (The executable here.)
//        //conf.IncludePaths.Add(@"[project.SourceRootPath]/..");
//        conf.IncludePaths.Add(@"[project.RootPath]/include");
//        conf.IncludePrivatePaths.Add(@"[project.SourceRootPath]");
//        // The library wants LIBRARY_COMPILE defined when it compiles the
//        // library, so that it knows whether it must use dllexport or
//        // dllimport.
//        conf.Defines.Add("LIBRARY_COMPILE");

//        if (target.OutputType == OutputType.Dll)
//        {
//            // We want this to output a shared library. (DLL)
//            conf.Output = Configuration.OutputType.Dll;

//            // This library project expects LIBRARY_DLL symbol to be defined
//            // when used as a DLL. While we could define it in the executable,
//            // it is better to put it as an exported define. That way, any
//            // projects with a dependency on this one will have LIBRARY_DLL
//            // automatically defined by Sharpmake.
//            conf.ExportDefines.Add("LIBRARY_DLL");

//            // Exported defines are not necessarily defines as well, so we need
//            // to add LIBRARY_DLL as an ordinary define too.
//            conf.Defines.Add("LIBRARY_DLL");
//        }
//        else if (target.OutputType == OutputType.Lib)
//        {
//            // We want this to output a static library. (LIB)
//            conf.Output = Configuration.OutputType.Lib;
//        }

//        if (target.Platform == Platform.win64)
//        {
//            conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);
//            conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.CPP17);
//        }
//    }
//}


//// The executable that consumes the library.
//[Generate]
//class TestProject : BaseLibraryProject
//{
//    public TestProject()
//    {
//        Name = "test";
//        SourceRootPath = @"[project.SharpmakeCsPath]/test/src";
//        RootPath = @"[project.SharpmakeCsPath]/xtl";
//    }

//    public override void ConfigureAll(Project.Configuration conf, Target target)
//    {
//        base.ConfigureAll(conf, target);
//        conf.IncludePrivatePaths.Add(@"[project.SourceRootPath]");
//        // This line tells Sharpmake that this project has a dependency on the
//        // library project. This will cause all exported include paths and
//        // exported defines to be automatically added to this project.
//        conf.AddPrivateDependency<XtlLibrary>(target);

//        if (target.Platform == Platform.win64)
//        {
//            conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);
//            conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.CPP17);
//        }
//    }
//}


//// The solution. It contains both the executable and the library.
//[Generate]
//public class XtlSolution : Solution
//{
//    public XtlSolution()
//    {
//        Name = "xtl";
//        AddTargets(new Target(
//            Platform.win32 | Platform.win64,
//            DevEnv.vs2019,
//            Optimization.Debug | Optimization.Release,
//            OutputType.Dll | OutputType.Lib));
//    }

//    [Configure]
//    public void ConfigureAll(Solution.Configuration conf, Target target)
//    {
//        conf.Name = @"[target.Optimization]_[target.OutputType]";
//        conf.SolutionPath = @"[solution.SharpmakeCsPath]\generated";

//        // Adds the projects to the solution. Note that because the executable
//        // has a dependency to the library, Sharpmake can automatically figures
//        // out that it should add the library to the solution too, so the
//        // second line is not actually needed.
//        conf.AddProject<TestProject>(target);
//        conf.AddProject<XtlLibrary>(target);

//        if (target.Platform == Platform.win64)
//        {
//            conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);
//            conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.CPP17);
//        }
//    }
//}

//public static class Main
//{
//    [Sharpmake.Main]
//    public static void SharpmakeMain(Sharpmake.Arguments arguments)
//    {
//        // Tells Sharpmake to generate the solution described by
//        // XtlSolution.
//        arguments.Generate<XtlSolution>();
//    }
//}


using System.IO;
using Sharpmake;


[Generate]
public class XtlLibrary : Project
{
    public XtlLibrary()
    {
        Name = "XtlLibrary";
        SourceRootPath = @"[project.SharpmakeCsPath]\xtl\src";
        AdditionalSourceRootPaths.Add(@"[project.SharpmakeCsPath]\xtl\include");
        RootPath = @"[project.SharpmakeCsPath]\xtl";

        AddTargets(new Target(
            Platform.win64 | Platform.orbis,
            DevEnv.vs2019,
            Optimization.Debug | Optimization.Release,
            OutputType.Lib));

    }


    [Configure]
    public void ConfigureAll(Project.Configuration conf, Target target)
    {
        //conf.ProjectPath = Path.Combine("[project.SharpmakeCsPath]", "projects");
        conf.ProjectPath = Path.Combine("[project.SharpmakeCsPath]/projects/[project.Name]");
        
        conf.IncludePaths.Add(@"[project.RootPath]\include");
        conf.IncludePrivatePaths.Add(@"[project.SourceRootPath]");
        //conf.IncludePrivatePaths.Add(@"[project.SharpmakeCsPath]\external\include");

        //conf.SourceFilesBuildExcludeRegex.Add(@"[project.SourceRootPath]\backend\directx\*");
        
        if (target.Platform == Platform.win64 | Platform.orbis)
        {
            conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.CPP17);
        }

        if (target.OutputType == OutputType.Lib)
        {
            conf.Output = Configuration.OutputType.Lib;
            conf.Defines.Add("RLTK_STATIC");
            conf.ExportDefines.Add("RLTK_STATIC");
        }


    }

}


[Generate]
public class TestProject : Project
{
    public TestProject()
    {
        Name = "TestProject";
        SourceRootPath = @"[project.SharpmakeCsPath]\test\src";
        RootPath = @"[project.SharpmakeCsPath]\test";

        AddTargets(new Target(
           Platform.win64 | Platform.orbis,
           DevEnv.vs2019,
           Optimization.Debug | Optimization.Release));

    }


    [Configure]
    public void ConfigureAll(Project.Configuration conf, Target target)
    {
        //conf.ProjectPath = Path.Combine("[project.SharpmakeCsPath]", "projects");
        conf.ProjectPath = Path.Combine("[project.SharpmakeCsPath]/projects/[project.Name]");

        conf.IncludePaths.Add(@"[project.SharpmakeCsPath]\RLtk\include");
        conf.IncludePrivatePaths.Add(@"[project.SourceRootPath]");
        conf.IncludePrivatePaths.Add(@"[project.RootPath]\include");

        conf.AddPrivateDependency<XtlLibrary>(target);

        if (target.Platform == Platform.win64)
        {
            conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.CPP17);
        }
    }

}


// Represents the solution that will be generated and that will contain the
// project with the sample code.
[Generate]
public class XtlSolution : Solution
{
    public XtlSolution()
    {

        // The name of the solution.
        Name = "XtlSolution";

        // As with the project, define which target this solution builds for.
        // It's usually the same thing.
        AddTargets(new Target(
            Platform.win64 | Platform.orbis,
            DevEnv.vs2019,
            Optimization.Debug | Optimization.Release));
    }

    // Configure for all 4 generated targets. Note that the type of the
    // configuration object is of type Solution.Configuration this time.
    // (Instead of Project.Configuration.)
    [Configure]
    public void ConfigureAll(Solution.Configuration conf, Target target)
    {
        // Puts the generated solution in the /generated folder too.
        conf.SolutionPath = @"[solution.SharpmakeCsPath]\projects";

        conf.AddProject<XtlLibrary>(target);
        conf.AddProject<TestProject>(target);

        if (target.Platform == Platform.win64)
        {
            conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.CPP17);
        }
    }
}


public static class Main
{
    [Sharpmake.Main]
    public static void SharpmakeMain(Sharpmake.Arguments arguments)
    {

        // Tells Sharpmake to generate the solution described by
        // BasicsSolution.
        arguments.Generate<XtlSolution>();
    }
}
