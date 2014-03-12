#include <TTL/TTL.hpp>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include "File.hpp"
#include <cstddef>
#include "Token.hpp"
#include "Cxy.hpp"
#include "Dxy.hpp"
#include "Path.hpp"
#include "Verbose.hpp"
#include "BlockPrinter.hpp"
#include "gmpxx.h"
#include <iomanip>
#include "Table.hpp"
#include "Register.hpp"


int main( int argc, char *argv[] )
{
//    Table<Register, Register> ax;
//    ax.push(Register("This"));
//    ax.push(Register("is"));
//    ax.push(Register("a string"));
//    Register inc(0);
//    ttl::Ips ips(30.f);
//    for (;inc.getNumber() < Register("7").getNumber(); inc++)
//    {
//        ips.limit();
////        std::cout << std::to_string(static_cast<std::size_t>(u.first)) + static_cast<std::string>(u.second) << '\n';
//        std::cout << inc.getString() << '\n';
//    }
//    Dxy dxy;
//    dxy.setData(ttl::file2str("../../tmp/regex.dxy"));
//    dxy.uncomment();
//    std::cout << "file: " << dxy << std::endl;
//    auto keywords ( dxy.tokenize() );
//    for (auto &token : keywords)
//    {
//        std::cout << "processing: " << token << std::endl;
//
//        if ( token.isLiteral() )
//        {
//            token.literate();
//            std::cout << "literated: " << token << std::endl;
//            token.escape();
//        }
//
//        std::cout << "finished: " << token << std::endl;
//    }
    // We now have all keywords, we need to put the tokens into a tokenized location.

//    return 0;

//
//    {
//        Dxy tokenizer;
//        tokenizer.setData(ttl::file2str("../../tmp/sample.dxy"));
//        tokenizer.uncomment();
//        auto x(tokenizer.tokenize());
//        for (auto &y : x)
//        {
//            if (y.isLiteral())
//            {
//                y.literate();
//                y.escape();
//            }
//            std::cout << '\'' << y << '\'' << std::endl;
//        }
//    }
//    return 0;
    BlockPrinter print;

    Cxy compiler;
    Dxy tokenizer;

    File file ( "../../tmp/sample.cxy" );
    file.parseAllIncludeStatements ( );
    print << "Entire file after including" << file;
    Nest x = file.getMostNestedCxy ( );
    while ( x.start != x.stop )
    {
        std::string statements ( x.start, x.stop );
        print << "Statements: " << statements;
        file.eraseNest ( x );
        x = file.getMostNestedCxy ( );
        std::string operating_data ( x.start, x.stop );
        tokenizer.setData ( std::move (statements) );
        auto tokens ( tokenizer.tokenize() );
        for ( auto &token : tokens )
        {
            if (token.isLiteral())
            {
                token.literate();
                token.escape();
            }
//            std::cout << '\'' << token << "'\n";
        }
        compiler.setTokens ( std::move ( tokens ) );
        operating_data = compiler.translate(operating_data);
        print << "Operating Data: " << operating_data;
    }
    return 0;

////    std::map<std::string, std::pair<long, std::string>> instructions;
////    auto cxy_settings = uncomment ( ttl::file2str ( "keywords.dxy" ) );
////    auto cxy_settings_tokenized = tokenize (cxy_settings);
////
////    for (decltype(cxy_settings_tokenized)::iterator it = cxy_settings_tokenized.begin(); it != cxy_settings_tokenized.end(); ++it)
////    {
////        std::string accessor ( std::move ( *it ) );
////        ++it;
////        std::string arguments ( std::move ( *it ) );
////        ++it;
////        std::string type ( std::move ( *it ) );
////        instructions.insert(std::make_pair(trim(accessor), std::make_pair(std::stoll(arguments), type)));
////    }
////
////    for ( auto &x : instructions )
////        std::cout << "'" << x.first << "'" << x.second.first << "' \"" << x.second.second << "\"\n";
////
////    return 0;
//
//    // Makes sure to end the ouput with a nice newline.
//    ttl::ScopedFunction sc([](){std::cout << '\n';});
//
//    Verbose verbose, output;
//
//    try
//    {
//        // Check if cxy has gotten any commands
//        if (argc <= 1) // One argument reserved for program instantiation.
//        {
//            std::cout
//                << "Error: No input argument(s) specified.\n"
//                << "Enter \"cxy --help\" without quotation marks for help.";
//            return 0;
//        }
//
//        // Parse the arguments
//        ttl::Argument argument_store;
//        argument_store.setInert('h'); argument_store.setInert("help");
//        argument_store.setInert('v'); argument_store.setInert("verbose");
//        argument_store.setInert('u'); argument_store.setInert("unsafe");
//        argument_store.setInert('s'); argument_store.setInert("silent");
//        argument_store.setInert('b'); argument_store.setInert("bytecode");
//        argument_store.setInert('o'); argument_store.setInert("output");
//        argument_store.pass(argc, argv);
//
//        // Set the output state
//        verbose.set(argument_store.isPassed('v') || argument_store.isPassed("verbose"));
//        output.set(argument_store.isPassed('o') || argument_store.isPassed("output"));
//
//        verbose << "Checking for unsafe flags (-u and --unsafe)\n";
//
//        // Check if any invalid flags have been passed, unless the unsafe flag is passed.
//        if (! (argument_store.isPassed('u') || argument_store.isPassed("unsafe")) )
//        {
//
//            verbose << "\tUnsafe flag not passed, checking all arguments.\n";
//
//            std::string legal_flags[]
//            {
//                "h", "help",
//                "m", "mirror",
//                "v", "verbose",
//                "u", "unsafe",
//                "s", "silent",
//                "o", "output",
//                "b", "bytecode"
//            };
//
//            auto iterator = argument_store.getFlagsAndParameters().begin();
//            auto stop = argument_store.getFlagsAndParameters().end();
//
//            for (; iterator != stop; ++iterator)
//            {
//                auto temporary = iterator->first;
//                for (std::size_t i = 0; i < 2 && temporary.size() > 0 && temporary.front() == '-'; ++i)
//                {
//                    temporary.erase(temporary.begin());
//                }
//
//
//                decltype(&legal_flags[0]) position
//                    =
//                    std::find
//                    (
//                        legal_flags,
//                        legal_flags + sizeof(legal_flags) / sizeof(decltype(legal_flags[0])),
//                        temporary
//                    );
//
//                if (position == legal_flags + sizeof(legal_flags) / sizeof(decltype(legal_flags[0])))
//                {
//                    std::cout << "The flag \"" << iterator->first << "\" is not a valid flag. Aborting.";
//                    return 0;
//                }
//            }
//            verbose << "\tNo invalid flags passed, continueing.\n";
//        }
//        else
//        {
//            verbose << "\tUnsafe flag passed, skipped argument validation.\n";
//        }
//
//        verbose << "Check if the help menu argument was passed\n";
//
//        // Check if we need only to display a help menu.
//        if (argument_store.isPassed('h') || argument_store.isPassed("help"))
//        {
//            verbose << "\tPrinting help menu\n";
//            std::cout
//                << "Cxy version 1.0\n"
//                << "Command line argument syntax:\n"
//                << "[] means optional.\n<> means user-filled in.\n| means \"or\".\n\"...\" means a variadic amount of arguments.\n"
//                << "() denotes evaluation order.\n\n"
//                << "Any of the following can be combined together unless stated otherwise.\n"
//                << "Example: \"cxy data.txt -u\"\n\n"
//                << "cxy [-h | --help] - display this help info.\n"
//                << "cxy <File1> <File2> ... - Run cxy on each file.\n"
//                << "cxy [-u | --unsafe] - Turns off safety features (faster)\n"
//                << "cxy [-o | --output] - Print output file to the screen.\n"
//                << "cxy [-s | --silent] - Do not execute \"show\" statements.\n"
//                << "cxy [(-m | --mirror) <Folder>] - Will copy all processed files into the folder, preserving path structure.\n"
//                << "cxy [-b | --bytecode] - Will output generated bytecode.";
//            return 0;
//        }
//
//        verbose << "Fetching the working directory\n";
//
//        std::string working_directory = boost::filesystem::current_path().generic_string();
//        working_directory.push_back('/'); // Because it ends without a separator.
//
//        verbose << "The working directory is: \"" << working_directory << "\"\nRemoving all operands that start with a ./\n";
//
//        std::vector<Path> paths;
//
//        for (std::size_t i = 0; i < argument_store.getOperandCount(); ++i)
//        {
//            paths.emplace_back ( argument_store.getOperand ( i ) );
//        }
//
//        // Remove all beginning ./, they're useless.
//        for (Path &path : paths)
//        {
//            verbose << "Start Operand: " << path << "\n";
//            path.eraseCurrentDirectorySymbols ();
//            verbose << "Finished Operand: " << path << "\n";
//        }
//        verbose << "\n";
//
//
//        // Setting up a possible mirror system.
//        verbose << "Checking if the mirror argument (-m | --mirror) was passed.\n";
//        {
//            std::string mirror_directory;
//
//            if (argument_store.isPassed('m') || argument_store.isPassed("mirror"))
//            {
//                verbose << "Mirroring passed, setting up the mirror system\n";
//
//                boost::filesystem::path mirror_path;
//
//                if (argument_store.isPassed('m'))
//                    mirror_path = argument_store.getArgument('m');
//                else if (argument_store.isPassed("mirror"))
//                    mirror_path = argument_store.getArgument("mirror");
//
//                if (mirror_path.is_relative())
//                {
//                    verbose << "The mirror path was relative!\n";
//                    mirror_directory = working_directory + mirror_path.generic_string();
//                }
//                else
//                {
//                    verbose << "The mirror path was not relative.\n";
//                    mirror_directory = mirror_path.generic_string();
//                }
//
//                if (mirror_directory.back() != '/')
//                    mirror_directory.push_back('/');
//
//
//                verbose << "Mirror around: \"" << mirror_directory << "\"\n";
//
//                // Since the mirror is on, we need to replace absolutely-pathed operands:
//                verbose << "Replacing all absolutely-pathed operands provided.\n";
//                for (std::size_t i = 0; i < argument_store.getOperandCount(); ++i)
//                {
//                    boost::filesystem::path path(argument_store.getOperand(i));
//                    if (path.is_absolute())
//                    {
//                        verbose << "Original: " << argument_store.getOperand(i) << "\n";
////                        argument_store.getOperand(i) = get_relative_to(path, working_directory);
////                        path = path.getPathRelativeTo(working_directory);
//                        verbose << "Replacement: " << argument_store.getOperand(i) << "\n";
//                    }
//                }
//
//            }
//
//            verbose << "Mirror into: " << mirror_directory << "\n";
//
//            // Process each operand (file).
//            // Add the working directory in front of every operand, considering every operand is a file to be worked on.
//            verbose << "Processing each file...\n";
//            for (Path &path : paths)
//            {
//                // We fetch the absolute file to process...
//                path.toAbsolutePath ( );
//                verbose << "The file to process: " << path << "\n";
//
//                // We process this file...
//                File obj( path.getString () );
////                obj.setShow(!(argument_store.isPassed('s') || argument_store.isPassed("silent")));
//                try
//                {
//                    verbose << "Reading the file into memory\n";
////                    obj.read();
//                    verbose << "Parsing all include statements\n";
//                    obj.parseAllIncludeStatements();
//                    verbose << "Lexing the statements\n";
//                    verbose << "Parsing the data\n";
////                    obj.parse();
//
//                    verbose << "Completed processing, preparing the output path\n";
//                    Path output_path ( mirror_directory + path.getPathRelativeTo ( Path ( mirror_directory ) ).getString () );
//                    output_path.collapseHierarchy ( );
//
//                    // If a reflected folder does not exist, create one:
//                    verbose << "Checking whether output path exists.\n";
//                    if (!boost::filesystem::exists( boost::filesystem::path( output_path.getString() ).parent_path() ))
//                    {
//                        boost::filesystem::create_directories( boost::filesystem::path( output_path.getString() ).parent_path() );
//                        verbose << "Path did not exist, created\n";
//                    }
//
//                    verbose << "Output path: \"" << output_path << "\"\n";
//                    std::fstream out( output_path.getString(), std::ios::out | std::ios::trunc | std::ios::binary );
////                    out << obj;
//                    verbose << "Data written.\n";
//
//                    if (argument_store.isPassed('b') || argument_store.isPassed("bytecode"))
//                    {
////                        const std::vector<std::string> &instructions = obj.getInstructions();
////                        if (instructions.size() > 0)
////                        {
////                            out.close();
////                            out.open(output_path + ".bxy", std::ios::out | std::ios::trunc);
////                            out << "#cxy starb\n";
////                            // Create instruction table with # of bytes required:
////                            for (std::size_t i = 0; i < instructions.size(); ++i)
////                            {
////                                write_var<std::size_t>(out, instructions[i].size());
////                                std::cout << "Writing instruction\n: " << instructions[i] << std::endl;
////                                out << instructions[i];
////                            }
////                            out << "\n#cxy stob";
////                        }
//                    }
////                    output << obj;
//                }
//                catch (std::exception &exc_obj)
//                {
//                    std::cout
//                        << "Error during the processing of the file: "
//                        << path
//                        << "\n> "
//                        << exc_obj.what()
//                        << "\n\n";
//                }
//            }
//        }
//    }
//    catch (std::exception &exc_obj)
//    {
//        std::cout << "An error occurred: " << exc_obj.what();
//    }

}
