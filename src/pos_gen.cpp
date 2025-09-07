#include "node.h"
#include "graph.h"
#include "pos_gen.h"
#include "graphics.h"
#include <cstdlib>  
#include <ctime>   
#include <iostream>
#include <vector>
#include <cmath>

int pos_gen::max_length = 7;
int pos_gen::max_dir = 2;

int pos_gen::getRandomLength() { return std::rand() % pos_gen::max_length + 1; }

int pos_gen::getRandomDir() { return std::rand() % pos_gen::max_dir + 1; }

std::array<int, 3> pos_gen::genFrom(Graph graph, Node src) {
    // 1 Pick a random direction based on dir. 
    // Example: 0 means in the x axis we substract
    //          1 means in the x axis we add
    // etc...
    // and we only chane ONE axis as you can see
    // That, alongside with the getClosestPos() makes it so that
    // No two edges collapse 
    // Then:
    // 2 Pick a random step length (1 to max_length)
    // 3 Move from the source node in that direction by that length
    // 4 Check distance to all existing nodes; if too close, try again
    // 5 Return the new position when it is far enough from other nodes
    int x_length = getRandomLength();
    int y_length = getRandomLength();
    int z_length = getRandomLength();

    int x_dir = getRandomDir();
    int y_dir = getRandomDir();
    int z_dir = getRandomDir();

    std::array<int, 3> next_pos = src.get_pos();
    float curClosestPos;

    do {
        switch (x_dir) {
            case 1:
                next_pos[0] -= x_length;
                break;
            case 2:
                next_pos[0] += x_length;
                break;
        }

        switch (y_dir) {
            case 1:
                next_pos[1] -= y_length;
                break;
            case 2:
                next_pos[1] += y_length;
                break;
        }

        switch (z_dir) {
            case 1:
                next_pos[2] -= z_length;
                break;
            case 2:
                next_pos[2] += z_length;
                break;
        }
        curClosestPos = getClosestPos(graph, next_pos);
    }while(curClosestPos < 1.0f);

    return next_pos;
}

float d(std::array<int, 3> from, std::array<int, 3>to) {
    return sqrt( pow( abs(static_cast<double>(from[0] - to[0])  ), 2) 
               + pow( abs(static_cast<double>(from[1] - to[1])  ), 2) 
               + pow( abs(static_cast<double>(from[2] - to[2])  ), 2
           ));
}

float pos_gen::getClosestPos(Graph graph, std::array<int, 3> pos) {
    float ans = INF;

    for (auto a : graph.get_nodes()) {
        if (a.get_pos() == pos) { continue; }  
        float dist = d(a.get_pos(), pos);
        ans = std::min(ans, dist);
    } 
    //std::cout << ans;
    return ans;
}
