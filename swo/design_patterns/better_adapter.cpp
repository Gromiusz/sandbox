#include <iostream>


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
protected:
    void freeData() { delete data; }
    void setData(JSONData* _data) { data = _data;}
public:
    DataAnalyticsTool(JSONData* _data) : data(_data) {}
    void analyseData() {
        std::cout << "Analysing Data " << data->getData() << std::endl;
    }
    virtual ~DataAnalyticsTool() = default;
};

class Adapter : public DataAnalyticsTool {
    XMLData* xmlData;
public:
    Adapter(XMLData* _xmlData) : xmlData(_xmlData), DataAnalyticsTool(new JSONData(_xmlData->getData())){
        std::cout << " Data has just be converted " << std::endl;
    }
    ~Adapter() {
        freeData();
    }
};

class Client {
public:
    void ProcessData(DataAnalyticsTool* tool) {
        tool->analyseData();
    }
};

int main() {
    Client* client = new Client;
    XMLData* xmlData = new XMLData("Sample XML Data");
    JSONData* jsonData = new JSONData("Sample JSON Data");
    DataAnalyticsTool* tool = new DataAnalyticsTool(jsonData);
    client->ProcessData(tool);

    DataAnalyticsTool* tool2 = new Adapter(xmlData);
    client->ProcessData(tool2);

    delete xmlData;
    delete jsonData;
    delete tool;
    delete tool2;
    delete client;

    return 0;
}
