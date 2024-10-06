#include <iostream>

// struct XMLData {
//     std::string data;
// };

class JSONData {
    std::string data;
public:
    JSONData(std::string _JSONData) : data(_JSONData) {}
    std::string getData() { return data;}
};

class XMLData {
    std::string data;
public:
    XMLData(std::string _XmlData) : data(_XmlData) {}
    std::string getData() { return data;}
};

class DataAnalyticsTool {
    JSONData* data;
public:
    DataAnalyticsTool() = default;
    DataAnalyticsTool(JSONData* _data) : data(_data) {}
    virtual void analyseData() {
        std::cout << "Analysing Data " << data->getData() << std::endl;
    }
    virtual ~DataAnalyticsTool() = default;
};

class Adapter : public DataAnalyticsTool {
    XMLData* xmlData;
    JSONData jsonData;
public:
    Adapter(XMLData* _xmlData) : xmlData(_xmlData), jsonData(xmlData->getData()){
        std::cout << " Data has just be converted " << std::endl;
    }
    void analyseData() override {
        std::cout << "Analysing Data " << jsonData.getData() << std::endl;
    }

};

class Client {
public:
    void ProcessData(DataAnalyticsTool* tool) {
        tool->analyseData();
    }
};

int main() {
    XMLData* xmlData = new XMLData("Sample XML Data");
    DataAnalyticsTool* tool = new Adapter(xmlData);
    Client* client = new Client;
    client->ProcessData(tool);

    delete xmlData;
    delete tool;
    delete client;

    return 0;
}
