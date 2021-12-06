#ifndef COORD_INPUT
#define COORD_INPUT

struct p_coord
{
    int x;
    int y;
};

bool coordValide(struct p_coord coord) {
    return coord.x>=0 && coord.y>=0;
}

bool coordEqual(struct p_coord a, struct p_coord b) {
    return a.x == b.x && a.y == b.y;
}

#endif //COORD_INPUT