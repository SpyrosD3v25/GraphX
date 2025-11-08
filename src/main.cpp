// src/main.cpp
#include "graphics.h"
#include "pos_gen.h"
#include "graph.h"
#include "node.h"
#include "config.h"

#include <GL/glut.h>
#include <array>
#include <iostream>
#include <ctime>   

void create_graph() {
    std::srand(std::time(NULL));
    Graph graph;

    Node first;
    std::array<int,3> origin = {0,0,0};
    first.set_pos(origin);
    graph.add_node(first);

    size_t prev_idx = graph.get_nodes().size() - 1;

    const int N = 100;
    for (int i = 0; i < N; ++i) {
        Node& prev_node = graph.get_nodes()[prev_idx];
        std::array<int,3> next_pos = pos_gen::genFrom(graph, prev_node);

        Node next;
        next.set_pos(next_pos);
        graph.add_node(next);

        size_t new_idx = graph.get_nodes().size() - 1;
        graph.add_edge(graph.get_nodes()[prev_idx], graph.get_nodes()[new_idx]);

        prev_idx = new_idx;
    }

    graph.print_graph();
    Graphics::graphs.push_back(graph);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    // THere should be a different class for this
    // Under tests
    // BEcause the only reason for not receiving a graph from an API
    // is to test it
    // so we should have something like
    // test graph

    //Main should be an endpoint: generate(graph)
    create_graph();
    Graphics::initialize();

    glutDisplayFunc(Graphics::display);
    glutReshapeFunc(Graphics::reshape);
    glutMainLoop();
    return 0;
}


/*
TODO:
1) Make endpoints (advanced)
2) use segment tree for getClosestPos (advanced)
3) Optimize using pointers whenever possible (easy)
4) Put create_graph under tests (medium)
5) Consider for live updates (elite) -> 1) required for this
6) Config system
7) Service Provider instead of singleton
8) Add algorithms visualization
    - Add coloring "current" node
    - Add algorithms
    - Interface for the user to request an algo

*/
