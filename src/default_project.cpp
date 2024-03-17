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
                      "\"D:/tools/vcpkg/installed/x64-windows/\",\n";
#elif defined(__linux__)
      dependencies << "\t\"vcpkg_path\" : "
                      "\"/home/sig/repo/vcpkg/installed/x64-linux/\",\n";
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
  std::ofstream clang_format(".clang_format");
  if (clang_format.is_open()) {
    clang_format << "---";
    clang_format << "Language:        Cpp ";
    clang_format << "AccessModifierOffset: -2";
    clang_format << "AlignAfterOpenBracket: Align";
    clang_format << "AlignConsecutiveMacros: false";
    clang_format << "AlignConsecutiveAssignments: false";
    clang_format << "AlignConsecutiveBitFields: false";
    clang_format << "AlignConsecutiveDeclarations: false";
    clang_format << "AlignEscapedNewlines: Right";
    clang_format << "AlignOperands:   Align";
    clang_format << "AlignTrailingComments: true";
    clang_format << "AllowAllArgumentsOnNextLine: true";
    clang_format << "AllowAllConstructorInitializersOnNextLine: true";
    clang_format << "AllowAllParametersOfDeclarationOnNextLine: true";
    clang_format << "AllowShortEnumsOnASingleLine: true";
    clang_format << "AllowShortBlocksOnASingleLine: Never";
    clang_format << "AllowShortCaseLabelsOnASingleLine: true";
    clang_format << "AllowShortFunctionsOnASingleLine: true";
    clang_format << "AllowShortLambdasOnASingleLine: All";
    clang_format << "AllowShortIfStatementsOnASingleLine: Never";
    clang_format << "AllowShortLoopsOnASingleLine: true";
    clang_format << "AlwaysBreakAfterDefinitionReturnType: None";
    clang_format << "AlwaysBreakAfterReturnType: None";
    clang_format << "AlwaysBreakBeforeMultilineStrings: false";
    clang_format << "AlwaysBreakTemplateDeclarations: MultiLine";
    clang_format << "BinPackArguments: true";
    clang_format << "BinPackParameters: true";
    clang_format << "BraceWrapping:";
    clang_format << "  AfterCaseLabel:  false";
    clang_format << "  AfterClass:      true";
    clang_format << "  AfterControlStatement: Always";
    clang_format << "  AfterEnum:       true";
    clang_format << "  AfterFunction:   true";
    clang_format << "  AfterNamespace:  true";
    clang_format << "  AfterObjCDeclaration: true";
    clang_format << "  AfterStruct:     true";
    clang_format << "  AfterUnion:      false";
    clang_format << "  AfterExternBlock: true";
    clang_format << "  BeforeCatch:     true";
    clang_format << "  BeforeElse:      true";
    clang_format << "  BeforeLambdaBody: false";
    clang_format << "  BeforeWhile:     false";
    clang_format << "  IndentBraces:    false";
    clang_format << "  SplitEmptyFunction: false";
    clang_format << "  SplitEmptyRecord: false";
    clang_format << "  SplitEmptyNamespace: false";
    clang_format << "BreakBeforeBinaryOperators: None";
    clang_format << "BreakBeforeBraces: Custom";
    clang_format << "BreakBeforeInheritanceComma: false";
    clang_format << "BreakInheritanceList: BeforeColon";
    clang_format << "BreakBeforeTernaryOperators: true";
    clang_format << "BreakConstructorInitializersBeforeComma: false";
    clang_format << "BreakConstructorInitializers: BeforeColon";
    clang_format << "BreakAfterJavaFieldAnnotations: false";
    clang_format << "BreakStringLiterals: true";
    clang_format << "ColumnLimit:     0";
    clang_format << "CommentPragmas:  '^ IWYU pragma:'";
    clang_format << "CompactNamespaces: false";
    clang_format << "ConstructorInitializerAllOnOneLineOrOnePerLine: false";
    clang_format << "ConstructorInitializerIndentWidth: 2";
    clang_format << "ContinuationIndentWidth: 2";
    clang_format << "Cpp11BracedListStyle: true";
    clang_format << "DeriveLineEnding: true";
    clang_format << "DerivePointerAlignment: false";
    clang_format << "DisableFormat:   false";
    clang_format << "ExperimentalAutoDetectBinPacking: false";
    clang_format << "FixNamespaceComments: true";
    clang_format << "ForEachMacros:";
    clang_format << "  - foreach";
    clang_format << "  - Q_FOREACH";
    clang_format << "  - BOOST_FOREACH";
    clang_format << "IncludeBlocks:   Preserve";
    clang_format << "IncludeCategories:";
    clang_format << "  - Regex:           '^\"(llvm|llvm-c|clang|clang-c)/'";
    clang_format << "    Priority:        2";
    clang_format << "    SortPriority:    0";
    clang_format << "  - Regex:           '^(<|\"(gtest|gmock|isl|json)/)'";
    clang_format << "    Priority:        3";
    clang_format << "    SortPriority:    0";
    clang_format << "  - Regex:           '.*'";
    clang_format << "    Priority:        1";
    clang_format << "    SortPriority:    0";
    clang_format << "IncludeIsMainRegex: '(Test)?$'";
    clang_format << "IncludeIsMainSourceRegex: ''";
    clang_format << "IndentCaseLabels: false";
    clang_format << "IndentCaseBlocks: false";
    clang_format << "IndentGotoLabels: true";
    clang_format << "IndentPPDirectives: None";
    clang_format << "IndentExternBlock: AfterExternBlock";
    clang_format << "IndentWidth:     4";
    clang_format << "IndentWrappedFunctionNames: false";
    clang_format << "InsertTrailingCommas: None";
    clang_format << "JavaScriptQuotes: Leave";
    clang_format << "JavaScriptWrapImports: true";
    clang_format << "KeepEmptyLinesAtTheStartOfBlocks: true";
    clang_format << "MacroBlockBegin: ''";
    clang_format << "MacroBlockEnd:   ''";
    clang_format << "MaxEmptyLinesToKeep: 1";
    clang_format << "NamespaceIndentation: All";
    clang_format << "ObjCBinPackProtocolList: Auto";
    clang_format << "ObjCBlockIndentWidth: 2";
    clang_format << "ObjCBreakBeforeNestedBlockParam: true";
    clang_format << "ObjCSpaceAfterProperty: false";
    clang_format << "ObjCSpaceBeforeProtocolList: true";
    clang_format << "PenaltyBreakAssignment: 2";
    clang_format << "PenaltyBreakBeforeFirstCallParameter: 19";
    clang_format << "PenaltyBreakComment: 300";
    clang_format << "PenaltyBreakFirstLessLess: 120";
    clang_format << "PenaltyBreakString: 1000";
    clang_format << "PenaltyBreakTemplateDeclaration: 10";
    clang_format << "PenaltyExcessCharacter: 1000000";
    clang_format << "PenaltyReturnTypeOnItsOwnLine: 1000";
    clang_format << "PointerAlignment: Right";
    clang_format << "ReflowComments:  true";
    clang_format << "SortIncludes:    true";
    clang_format << "SortUsingDeclarations: true";
    clang_format << "SpaceAfterCStyleCast: false";
    clang_format << "SpaceAfterLogicalNot: false";
    clang_format << "SpaceAfterTemplateKeyword: true";
    clang_format << "SpaceBeforeAssignmentOperators: true";
    clang_format << "SpaceBeforeCpp11BracedList: false";
    clang_format << "SpaceBeforeCtorInitializerColon: true";
    clang_format << "SpaceBeforeInheritanceColon: true";
    clang_format << "SpaceBeforeParens: ControlStatements";
    clang_format << "SpaceBeforeRangeBasedForLoopColon: true";
    clang_format << "SpaceInEmptyBlock: false";
    clang_format << "SpaceInEmptyParentheses: false";
    clang_format << "SpacesBeforeTrailingComments: 1";
    clang_format << "SpacesInAngles:  false";
    clang_format << "SpacesInConditionalStatement: false";
    clang_format << "SpacesInContainerLiterals: true";
    clang_format << "SpacesInCStyleCastParentheses: false";
    clang_format << "SpacesInParentheses: false";
    clang_format << "SpacesInSquareBrackets: false";
    clang_format << "SpaceBeforeSquareBrackets: false";
    clang_format << "Standard:        Latest";
    clang_format << "StatementMacros:";
    clang_format << "  - Q_UNUSED";
    clang_format << "  - QT_REQUIRE_VERSION";
    clang_format << "TabWidth:        4";
    clang_format << "UseCRLF:         false";
    clang_format << "UseTab:          true";
    clang_format << "WhitespaceSensitiveMacros:";
    clang_format << "  - STRINGIZE";
    clang_format << "  - PP_STRINGIZE";
    clang_format << "  - BOOST_PP_STRINGIZE";
    clang_format << "...";
    clang_format.close();
    std::cout << "clang_format generated successfully.\n";
    return 0;
  } else {
    std::cerr << "Unable to open clang_format for writing.n";
    return 1;
  }
}