#ifndef __MAPSFORGE_POI_READER_HPP__
#define __MAPSFORGE_POI_READER_HPP__

#include <string>
#include <memory>
#include <fstream>
#include <map>
#include <vector>

#include "dictionary.hpp"
#include "database.hpp"
#include "geometry.hpp"

#include <pugixml.hpp>
#include <boost/optional/optional.hpp>
#include <boost/enable_shared_from_this.hpp>

struct POIData {
    double lat_, lon_ ;
    Dictionary tags_ ;
};

struct POIFileInfo {
    boost::optional<BBox> bounds_ ;
    std::string comment_, language_, writer_ ;
    time_t date_ ;
    int version_ ;
    bool has_ways_ ;
} ;

class POICategory: public boost::enable_shared_from_this<POICategory> {
public:

    using Ptr = std::shared_ptr<POICategory> ;
    using Collection = std::vector<Ptr> ;

    Collection descendants() const;
    Collection children() const { return children_ ; }

    std::string ID() const { return id_ ; }
    std::string name(const std::string &lang) const ;
    Ptr parent();

private:

    friend class POICategoryContainer ;

    std::vector<Ptr> children_ ;
    POICategory *parent_ = nullptr ;
    std::string title_, id_ ;

    std::map<std::string, std::string> lang_names_ ;

};

class POICategoryFilter {
public:
    void addCategory(const POICategory::Ptr &category);

    POICategory::Collection getCategories() const ;
    POICategory::Collection getTopLevelCategories() const ;

private:

    std::set<POICategory::Ptr> white_list_ ;
} ;

class POICategoryContainer {
  public:

    bool loadFromXML(const std::string &path) ;
    bool loadFromXMLString(const std::string &str) ;

    bool loadFromPOIFile(SQLite::Connection &db) ;

    POICategory::Ptr getByID(const std::string &id) ;

private:

    bool parseCategory(POICategory::Ptr &c, const pugi::xml_node &root) ;

    POICategory::Ptr root_ ;
    std::map<std::string, POICategory::Ptr> categories_ ;
};

class POIReader
{
public:

    POIReader() {}

    void open(const std::string &file_path) ;

    ~POIReader() {}


private:

    POICategoryContainer categories_ ;
    std::string poi_file_path_ ;
    SQLite::Connection db_ ;
};



#endif


