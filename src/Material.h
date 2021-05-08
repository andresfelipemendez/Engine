#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

class Material
{
private:
    /* data */
public:
    std::map<std::string, std::string> properties;
    Material(std::string materialFileName);
    ~Material();
};

Material::Material(std::string materialFileName)
{
    bool fileExists = std::filesystem::exists(materialFileName);

    std::fstream fs;
    fs.open(materialFileName, std::fstream::in);

    std::string line;
    while (std::getline(fs, line))
    {
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
        std::string key = line.substr(0, line.find_last_of(":"));
        std::string val = line.substr(line.find_last_of(":") + 1);

        if (key == "shader")
        {
            std::cout << "get shader:" << key << " : " << val << "\n";
            properties.emplace(key, val);
        }
    }

    fs.close();
}

Material::~Material()
{
}
