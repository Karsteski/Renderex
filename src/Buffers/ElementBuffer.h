#include <string>
#include <vector>

class ElementBuffer {
public:
    ElementBuffer(std::string name, std::vector<unsigned int> data);

    std::string getName();
    unsigned int getID();
    int getNumberOfBytes();
    int getNumberOfIndices();
    const std::vector<unsigned int>& getElements();

private:
    std::string m_name;
    unsigned int m_ebo_ID;
    std::vector<unsigned int> m_data;
};
