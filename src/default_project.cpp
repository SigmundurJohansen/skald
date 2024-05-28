#include "default_project.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

int make_dependencies() {
  std::ofstream dependencies("dependencies.json");
  if (dependencies.is_open()) {
    const char *myVar = std::getenv("vcpkg_path");
    dependencies << "{ \n";
    if (myVar) {
      std::cout << "vcpkg_path exists: " << myVar << std::endl;
      dependencies << "\t\"vcpkg_path\" : \"" << myVar << "\",\n";
    } else {
      std::cout << "vcpkg_path does not exist" << std::endl;
#if defined(_WIN32) || defined(_WIN64)
      dependencies << "\t\"vcpkg_path\" : "
                      "\"D:/tools/vcpkg\",\n";
#elif defined(__linux__)
      dependencies << "\t\"vcpkg_path\" : "
                      "\"/home/sig/repo/vcpkg\",\n";
#endif
    }
    dependencies << "\t\"dependencies\" : [\"fmt\"],\n"
                 << "\t\"includes\" : []\n"
                 << "}";
    dependencies.close();
    std::cout << "dependencies generated successfully.\n";
    return 0;
  } else {
    std::cerr << "Unable to open dependencies for writing.\n";
    return 1;
  }
}

int make_compiler_flags() {
  std::ofstream settings("settings.json");
  if (settings.is_open()) {
    settings << "{ \n";
    settings << "\t\"project_name\" : \"new_project\",\n"
             << "\t\"compiler\": \"clang\",\"\n"
             << "\t\"compiler_flag\" : [";
    settings << "\"-g\",";
    settings << "\"-std=c++20\",";
    settings << "\"-Wall\",";
    settings << "\"-fstack-usage\"";
    settings << "]\n";
    settings << "}";
    settings.close();
    std::cout << "settings generated successfully.\n";
    return 0;
  } else {
    std::cerr << "Unable to open settings for writing.n";
    return 1;
  }
}

int make_example_code() {
  std::ofstream main_file("main.cpp");
  if (main_file.is_open()) {
    main_file << "#include <fmt/core.h>\n";
    main_file << "#include <fmt/color.h>\n";
    main_file << "#include <string>\n\n";
    main_file << "int main() {\n";
    main_file << "  fmt::print(fg(fmt::color::crimson)";
    main_file << "| fmt::emphasis::bold, \"Hello, {}!\", \"world\");\n";
    main_file << "}\n";
    main_file.close();
    std::cout << "main_file generated successfully.\n";
    return 0;
  } else {
    std::cerr << "Unable to open main_file for writing.n";
    return 1;
  }
}

int clang_format() {
  std::ofstream clang_format(".clang-format");
  if (clang_format.is_open()) {
    clang_format << "---\n";
    clang_format << "Language:        Cpp \n";
    clang_format << "AccessModifierOffset: -2\n";
    clang_format << "AlignAfterOpenBracket: Align\n";
    clang_format << "AlignConsecutiveMacros: false\n";
    clang_format << "AlignConsecutiveAssignments: false\n";
    clang_format << "AlignConsecutiveBitFields: false\n";
    clang_format << "AlignConsecutiveDeclarations: false\n";
    clang_format << "AlignEscapedNewlines: Right\n";
    clang_format << "AlignOperands:   Align\n";
    clang_format << "AlignTrailingComments: true\n";
    clang_format << "AllowAllArgumentsOnNextLine: true\n";
    clang_format << "AllowAllConstructorInitializersOnNextLine: true\n";
    clang_format << "AllowAllParametersOfDeclarationOnNextLine: true\n";
    clang_format << "AllowShortEnumsOnASingleLine: true\n";
    clang_format << "AllowShortBlocksOnASingleLine: Never\n";
    clang_format << "AllowShortCaseLabelsOnASingleLine: true\n";
    clang_format << "AllowShortFunctionsOnASingleLine: true\n";
    clang_format << "AllowShortLambdasOnASingleLine: All\n";
    clang_format << "AllowShortIfStatementsOnASingleLine: Never\n";
    clang_format << "AllowShortLoopsOnASingleLine: true\n";
    clang_format << "AlwaysBreakAfterDefinitionReturnType: None\n";
    clang_format << "AlwaysBreakAfterReturnType: None\n";
    clang_format << "AlwaysBreakBeforeMultilineStrings: false\n";
    clang_format << "AlwaysBreakTemplateDeclarations: MultiLine\n";
    clang_format << "BinPackArguments: true\n";
    clang_format << "BinPackParameters: true\n";
    clang_format << "BraceWrapping:\n";
    clang_format << "  AfterCaseLabel:  false\n";
    clang_format << "  AfterClass:      true\n";
    clang_format << "  AfterControlStatement: Always\n";
    clang_format << "  AfterEnum:       true\n";
    clang_format << "  AfterFunction:   true\n";
    clang_format << "  AfterNamespace:  true\n";
    clang_format << "  AfterObjCDeclaration: true\n";
    clang_format << "  AfterStruct:     true\n";
    clang_format << "  AfterUnion:      false\n";
    clang_format << "  AfterExternBlock: true\n";
    clang_format << "  BeforeCatch:     true\n";
    clang_format << "  BeforeElse:      true\n";
    clang_format << "  BeforeLambdaBody: false\n";
    clang_format << "  BeforeWhile:     false\n";
    clang_format << "  IndentBraces:    false\n";
    clang_format << "  SplitEmptyFunction: false\n";
    clang_format << "  SplitEmptyRecord: false\n";
    clang_format << "  SplitEmptyNamespace: false\n";
    clang_format << "BreakBeforeBinaryOperators: None\n";
    clang_format << "BreakBeforeBraces: Custom\n";
    clang_format << "BreakBeforeInheritanceComma: false\n";
    clang_format << "BreakInheritanceList: BeforeColon\n";
    clang_format << "BreakBeforeTernaryOperators: true\n";
    clang_format << "BreakConstructorInitializersBeforeComma: false\n";
    clang_format << "BreakConstructorInitializers: BeforeColon\n";
    clang_format << "BreakAfterJavaFieldAnnotations: false\n";
    clang_format << "BreakStringLiterals: true\n";
    clang_format << "ColumnLimit:     0\n";
    clang_format << "CommentPragmas:  '^ IWYU pragma:'\n";
    clang_format << "CompactNamespaces: false\n";
    clang_format << "ConstructorInitializerAllOnOneLineOrOnePerLine: false\n";
    clang_format << "ConstructorInitializerIndentWidth: 2\n";
    clang_format << "ContinuationIndentWidth: 2\n";
    clang_format << "Cpp11BracedListStyle: true\n";
    clang_format << "DeriveLineEnding: true\n";
    clang_format << "DerivePointerAlignment: false\n";
    clang_format << "DisableFormat:   false\n";
    clang_format << "ExperimentalAutoDetectBinPacking: false\n";
    clang_format << "FixNamespaceComments: true\n";
    clang_format << "ForEachMacros:\n";
    clang_format << "  - foreach\n";
    clang_format << "  - Q_FOREACH\n";
    clang_format << "  - BOOST_FOREACH\n";
    clang_format << "IncludeBlocks:   Preserve\n";
    clang_format << "IncludeCategories:\n";
    clang_format << "  - Regex:           '^\"(llvm|llvm-c|clang|clang-c)/'\n";
    clang_format << "    Priority:        2\n";
    clang_format << "    SortPriority:    0\n";
    clang_format << "  - Regex:           '^(<|\"(gtest|gmock|isl|json)/)'\n";
    clang_format << "    Priority:        3\n";
    clang_format << "    SortPriority:    0\n";
    clang_format << "  - Regex:           '.*'\n";
    clang_format << "    Priority:        1\n";
    clang_format << "    SortPriority:    0\n";
    clang_format << "IncludeIsMainRegex: '(Test)?$'\n";
    clang_format << "IncludeIsMainSourceRegex: ''\n";
    clang_format << "IndentCaseLabels: false\n";
    clang_format << "IndentCaseBlocks: false\n";
    clang_format << "IndentGotoLabels: true\n";
    clang_format << "IndentPPDirectives: None\n";
    clang_format << "IndentExternBlock: AfterExternBlock\n";
    clang_format << "IndentWidth:     4\n";
    clang_format << "IndentWrappedFunctionNames: false\n";
    clang_format << "InsertTrailingCommas: None\n";
    clang_format << "JavaScriptQuotes: Leave\n";
    clang_format << "JavaScriptWrapImports: true\n";
    clang_format << "KeepEmptyLinesAtTheStartOfBlocks: true\n";
    clang_format << "MacroBlockBegin: ''\n";
    clang_format << "MacroBlockEnd:   ''\n";
    clang_format << "MaxEmptyLinesToKeep: 1\n";
    clang_format << "NamespaceIndentation: All\n";
    clang_format << "ObjCBinPackProtocolList: Auto\n";
    clang_format << "ObjCBlockIndentWidth: 2\n";
    clang_format << "ObjCBreakBeforeNestedBlockParam: true\n";
    clang_format << "ObjCSpaceAfterProperty: false\n";
    clang_format << "ObjCSpaceBeforeProtocolList: true\n";
    clang_format << "PenaltyBreakAssignment: 2\n";
    clang_format << "PenaltyBreakBeforeFirstCallParameter: 19\n";
    clang_format << "PenaltyBreakComment: 300\n";
    clang_format << "PenaltyBreakFirstLessLess: 120\n";
    clang_format << "PenaltyBreakString: 1000\n";
    clang_format << "PenaltyBreakTemplateDeclaration: 10\n";
    clang_format << "PenaltyExcessCharacter: 1000000\n";
    clang_format << "PenaltyReturnTypeOnItsOwnLine: 1000\n";
    clang_format << "PointerAlignment: Right\n";
    clang_format << "ReflowComments:  true\n";
    clang_format << "SortIncludes:    true\n";
    clang_format << "SortUsingDeclarations: true\n";
    clang_format << "SpaceAfterCStyleCast: false\n";
    clang_format << "SpaceAfterLogicalNot: false\n";
    clang_format << "SpaceAfterTemplateKeyword: true\n";
    clang_format << "SpaceBeforeAssignmentOperators: true\n";
    clang_format << "SpaceBeforeCpp11BracedList: false\n";
    clang_format << "SpaceBeforeCtorInitializerColon: true\n";
    clang_format << "SpaceBeforeInheritanceColon: true\n";
    clang_format << "SpaceBeforeParens: ControlStatements\n";
    clang_format << "SpaceBeforeRangeBasedForLoopColon: true\n";
    clang_format << "SpaceInEmptyBlock: false\n";
    clang_format << "SpaceInEmptyParentheses: false\n";
    clang_format << "SpacesBeforeTrailingComments: 1\n";
    clang_format << "SpacesInAngles:  false\n";
    clang_format << "SpacesInConditionalStatement: false\n";
    clang_format << "SpacesInContainerLiterals: true\n";
    clang_format << "SpacesInCStyleCastParentheses: false\n";
    clang_format << "SpacesInParentheses: false\n";
    clang_format << "SpacesInSquareBrackets: false\n";
    clang_format << "SpaceBeforeSquareBrackets: false\n";
    clang_format << "Standard:        Latest\n";
    clang_format << "StatementMacros:\n";
    clang_format << "  - Q_UNUSED\n";
    clang_format << "  - QT_REQUIRE_VERSION\n";
    clang_format << "TabWidth:        4\n";
    clang_format << "UseCRLF:         false\n";
    clang_format << "UseTab:          true\n";
    clang_format << "WhitespaceSensitiveMacros:\n";
    clang_format << "  - STRINGIZE\n";
    clang_format << "  - PP_STRINGIZE\n";
    clang_format << "  - BOOST_PP_STRINGIZE\n";
    clang_format << "...\n";
    clang_format.close();
    std::cout << "clang_format generated successfully.\n";
    return 0;
  } else {
    std::cerr << "Unable to open clang_format for writing.n";
    return 1;
  }
}
