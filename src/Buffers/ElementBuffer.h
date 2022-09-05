#include <string>
#include <vector>

class ElementBuffer {
public:
    ElementBuffer(std::string name, std::vector<unsigned int> data);

    std::string getName() const;
    unsigned int getID() const;
    int getNumberOfBytes() const;
    int getNumberOfIndices() const;
    const std::vector<unsigned int>& getElements() const;

private:
    std::string m_name;
    unsigned int m_ebo_ID;
    std::vector<unsigned int> m_data;
};
