#include <benchmark/benchmark.h>
#include <iostream>





class CustomReporter : public benchmark::ConsoleReporter
{
public:
    void ReportRuns(const std::vector<Run>& reports) override
    {

        if (!reports.empty())
        {
            const std::string& name = reports.front().benchmark_name();

            std::string group;
            const size_t firstTemplateOpenBracket = name.find_first_of('<');
            if (firstTemplateOpenBracket != std::string::npos)
            {
                const size_t firstTemplateCloseBracket = name.find_first_of('>', firstTemplateOpenBracket);

                std::string_view groupV(name.data() + firstTemplateOpenBracket,
                                        name.data() + firstTemplateCloseBracket);
                std::string templateType = std::string(groupV);
                if (m_previousTemplate != templateType)
                {
                    GetOutputStream() << '\n';
                }

                m_previousTemplate = templateType;
            }
            else
            {
                static std::string previousGroup;
                if (name.find("Matrix") != std::string::npos)
                    group = "Matrix";
                else if (name.find("Vector") != std::string::npos)
                    group = "Vector";

                if (!previousGroup.empty() && group != previousGroup)
                    GetOutputStream() << '\n';

                previousGroup = group;
            }
        }

        benchmark::ConsoleReporter::ReportRuns(reports);
    }

    std::string m_previousTemplate;
};

int main(int argc, char** argv)
{
    benchmark::Initialize(&argc, argv);
    CustomReporter reporter;

    benchmark::RunSpecifiedBenchmarks(&reporter);

    benchmark::Shutdown();

    return 0;
}
