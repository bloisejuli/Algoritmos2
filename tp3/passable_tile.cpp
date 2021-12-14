#include "passable_tile.h"

PassableTile::PassableTile (char tile_type) {

    material_contained = 0;

    if(tile_type == ROAD)
        this->tile_type = ROAD;

    else if(tile_type == BITUMEN)
        this->tile_type = BITUMEN;

    else if(tile_type == DOCK)
        this->tile_type = DOCK;

}

void PassableTile::add_material(Material* material) {
    material_contained = material;
}

void PassableTile::remove_material() {
    delete material_contained;
    material_contained = 0;
}

void PassableTile::show() {
    cout << "Consulted tile is " << BOLD_BLUE << PASSABLE << DEFAULT_COLOR << ", specifically a " <<
         get_tile_type_color() << get_full_tile_type(get_tile_type()) << DEFAULT_COLOR << " and is ";

    if (tile_empty())
        cout << BOLD_GREEN << state_of_tile() << DEFAULT_COLOR << '\n';
    else
        cout << BOLD_RED << state_of_tile() << DEFAULT_COLOR << ", it contains a: " <<
             BOLD_GREEN << material_contained->get_material() << DEFAULT_COLOR << '\n';
}

string PassableTile::get_value() {
    if(material_contained != 0)
        return material_contained->get_material();
    else
        return "";
}

int PassableTile::get_material_amount() {
    if(material_contained != 0)
        return material_contained->get_quantity();
    else
        return 0;
}

bool PassableTile::tile_empty() {
    if (material_contained == 0 && player_on_it == 0)
        return true;

    return false;
}

string PassableTile::state_of_tile() {
    if (tile_empty())
        return EMPTY;

    return OCCUPIED;
}

string PassableTile::get_tile_class() {
    return PASSABLE;
}

char PassableTile::get_tile_type() {
    return tile_type;
}

string PassableTile::get_full_tile_type(char tile_acronym) {
    string tile_name;

    if (tile_acronym == ROAD)
        tile_name = ROAD_TYPE;
    else if (tile_acronym == BITUMEN)
        tile_name = BITUMEN_TYPE;
    else if (tile_acronym == DOCK)
        tile_name = DOCK_TYPE;

    return tile_name;
}

string PassableTile::get_tile_type_color() {
    string tile_color;

    if (tile_type == ROAD)
        tile_color = BOLD_GREY;
    else if (tile_type == BITUMEN)
        tile_color = BOLD_BLACK;
    else if (tile_type == DOCK)
        tile_color = BOLD_BROWN;

    return tile_color;
}

PassableTile::~PassableTile() {
    if (material_contained != 0)
        delete material_contained;
}
