#define MAIN

#include <gtest/gtest.h>
#include "common.cc"
#include "data-structure/graph.cc"
#include "algorithm/traverse.cc"
#include "../graph_utils.h"

GRAPH_TEST(DfsTest);
GRAPH_TEST(BfsTest);
LABELED_GRAPH_TEST(01BfsTest);

using namespace graph;

TYPED_TEST(g_DfsTest, SimpleTest) {
    std::vector<size_t> nodes;
    dfs_with_duplicate_vertices(this->mkGraph({{0, 1}, {1, 2}, {2, 3}, {1, 3}}), {0}, [&](auto x) {
        nodes.push_back(get<1>(x));
        return false;
    }, [](const auto& edge __attribute__((unused))) { return true; });

    EXPECT_EQ(4, nodes.size());
    EXPECT_EQ(1, nodes[0]);
    EXPECT_EQ(3, nodes[1]);
    EXPECT_EQ(2, nodes[2]);
    EXPECT_EQ(3, nodes[3]);

    nodes.clear();
    dfs(this->mkGraph({{0, 1}, {0, 3}, {1, 2}, {3, 4}}), {0}, [&](auto x) {
        nodes.push_back(get<1>(x));
        return false;
    });

    EXPECT_EQ(4, nodes.size());
    EXPECT_TRUE(nodes[0] == 1 || nodes[0] == 3);
    EXPECT_EQ((nodes[0] == 1) ? 2 : 4, nodes[1]);
    EXPECT_TRUE(nodes[2] == 1 || nodes[2] == 3);
    EXPECT_EQ((nodes[2] == 1) ? 2 : 4, nodes[3]);
}
TYPED_TEST(g_DfsTest, BreakTest) {
    std::vector<size_t> nodes;
    dfs_with_duplicate_vertices(this->mkGraph({{0, 1}, {0, 2}, {1, 2}}), {0}, [&](auto x) {
        nodes.push_back(get<1>(x));
        return get<1>(x) == 1;
    }, [](const auto& edge __attribute__((unused))) { return true; });

    EXPECT_EQ(1, nodes.back());
}
TYPED_TEST(g_DfsTest, IsAddedTest) {
    std::vector<size_t> nodes;
    dfs_with_duplicate_vertices(this->mkGraph({{0, 1}, {0, 2}, {1, 2}}), {0}, [&](auto x) {
        nodes.push_back(get<1>(x));
        return false;
    }, [](const auto& edge) { return get<1>(edge) != 2; });

    EXPECT_EQ(1, nodes.size());
    EXPECT_EQ(1, nodes[0]);
}

TYPED_TEST(g_BfsTest, SimpleTest) {
    std::vector<size_t> nodes;
    bfs_with_duplicate_vertices(this->mkGraph({{0, 1}, {1, 2}, {2, 3}, {1, 3}}), {0}, [&](auto x) {
        nodes.push_back(get<1>(x));
        return false;
    }, [](const auto& edge __attribute__((unused))) { return true; });

    EXPECT_EQ(4, nodes.size());
    EXPECT_EQ(1, nodes[0]);
    EXPECT_EQ(2, nodes[1]);
    EXPECT_EQ(3, nodes[2]);
    EXPECT_EQ(3, nodes[3]);

    nodes.clear();
    bfs(this->mkGraph({{0, 1}, {0, 3}, {1, 2}, {3, 4}}), {0}, [&](auto x) {
        nodes.push_back(get<1>(x));
        return false;
    });

    EXPECT_EQ(4, nodes.size());
    EXPECT_TRUE(nodes[0] == 1 || nodes[0] == 3);
    EXPECT_EQ((nodes[0] == 1) ? 3 : 1, nodes[1]);
    EXPECT_TRUE(nodes[2] == 2 || nodes[2] == 4);
    EXPECT_EQ((nodes[2] == 2) ? 4 : 2, nodes[3]);
}
TYPED_TEST(g_BfsTest, BreakTest) {
    std::vector<size_t> nodes;
    bfs_with_duplicate_vertices(this->mkGraph({{0, 1}, {1, 2}, {1, 3}}), {0}, [&](auto x) {
        nodes.push_back(get<1>(x));
        return get<1>(x) == 1;
    }, [](const auto& edge __attribute__((unused))) { return true; });

    EXPECT_EQ(1, nodes.back());
}
TYPED_TEST(g_BfsTest, IsAddedTest) {
    std::vector<size_t> nodes;
    bfs_with_duplicate_vertices(this->mkGraph({{0, 1}, {0, 2}, {1, 2}}), {0}, [&](auto x) {
        nodes.push_back(get<1>(x));
        return false;
    }, [](const auto& edge) { return get<1>(edge) != 2; });

    EXPECT_EQ(1, nodes.size());
    EXPECT_EQ(1, nodes[0]);
}

TYPED_TEST(g_01BfsTest, SimpleTest) {
    std::vector<std::tuple<size_t, size_t, int>> edges;
    edges.push_back({0, 1, 1});
    edges.push_back({0, 2, 0});
    edges.push_back({1, 3, 0});
    edges.push_back({2, 4, 1});

    auto g = this->mkGraph(edges);
    std::vector<size_t> nodes;
    zero_one_bfs(g, {0}, [&](const auto &edge) {
        nodes.push_back(get<1>(edge));
        return false;
    });

    EXPECT_EQ(std::vector<size_t>({2, 1, 3, 4}), nodes);
}
