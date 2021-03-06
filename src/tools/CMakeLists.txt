SET ( RSC_TOOL_SOURCES
	${SRC_ROOT}/util/database.cpp
	${SRC_ROOT}/util/database.hpp
	${SRC_ROOT}/util/dictionary.cpp
	${SRC_ROOT}/util/dictionary.hpp
	${SRC_ROOT}/tools/makeres.cpp
)

ADD_EXECUTABLE(makeres ${RSC_TOOL_SOURCES})
TARGET_LINK_LIBRARIES(makeres sqlite3 ${Boost_LIBRARIES} pthread dl z)

SET ( RENDER_TILE_SOURCES
	${SRC_ROOT}/io/mapsforge_map_reader.cpp
	${SRC_ROOT}/io/serializer.cpp

	${SRC_ROOT}/util/dictionary.cpp
	${SRC_ROOT}/util/dictionary.hpp
	${SRC_ROOT}/3rdparty/pugixml/pugixml.cpp

	${SRC_ROOT}/tools/render_tile.cpp
)


ADD_EXECUTABLE(render_tile ${RENDER_TILE_SOURCES})
TARGET_LINK_LIBRARIES(render_tile mapsforge_renderer ${Boost_LIBRARIES})

ADD_EXECUTABLE(query_poi
    ${SRC_ROOT}/io/mapsforge_poi_reader.cpp
    ${SRC_ROOT}/util/database.cpp
    ${SRC_ROOT}/util/database.hpp
    ${SRC_ROOT}/util/dictionary.cpp
    ${SRC_ROOT}/util/dictionary.hpp
    ${SRC_ROOT}/3rdparty/pugixml/pugixml.cpp
    ${SRC_ROOT}/io/poi_categories.hpp
    ${SRC_ROOT}/io/poi_categories.cpp
    ${SRC_ROOT}/tools/query_poi.cpp
    )

TARGET_LINK_LIBRARIES(query_poi sqlite3 ${Boost_LIBRARIES} dl)

ADD_EXECUTABLE(map_info
    ${SRC_ROOT}/io/mapsforge_map_reader.cpp
    ${SRC_ROOT}/io/serializer.cpp
    ${SRC_ROOT}/util/tms.cpp

    ${SRC_ROOT}/util/dictionary.cpp
    ${SRC_ROOT}/util/dictionary.hpp
    ${SRC_ROOT}/3rdparty/pugixml/pugixml.cpp

    ${SRC_ROOT}/tools/map_info.cpp)

TARGET_LINK_LIBRARIES(map_info ${Boost_LIBRARIES})

#ADD_EXECUTABLE(test_spirit test_spirit.cpp ${SRC_ROOT}/tools/luapp/impl.cpp)
#TARGET_LINK_LIBRARIES(test_spirit ${LUA_LIBRARIES} ${LUABIND_LIBRARIES} ${Boost_LIBRARIES})
