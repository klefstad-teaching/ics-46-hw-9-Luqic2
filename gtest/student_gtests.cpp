#include <gtest/gtest.h>

#include "../src/dijkstras.h"
#include "../src/ladder.h"

TEST(v, testLoadWords) {
  set<string> word_list;
  load_words(word_list, "src/shortWords.txt");

  EXPECT_EQ(word_list.size(), 14);
}

TEST(WordLadder, testEditDistanceWithin) {
  EXPECT_TRUE(edit_distance_within("bear", "hear", 1));

  EXPECT_TRUE(edit_distance_within("chair", "hair", 1));

  EXPECT_TRUE(edit_distance_within("cheat", "chat", 1));

  EXPECT_TRUE(edit_distance_within("car", "care", 1));

  EXPECT_TRUE(edit_distance_within("were", "were", 1));

  EXPECT_FALSE(edit_distance_within("ware", "fair", 1));
}

TEST(WordLadder, testGenerateWordLadder_shortWords) {
  set<string> word_list;
  load_words(word_list, "src/shortWords.txt");

  vector<string> wordLadder1 = generate_word_ladder("car", "cheat", word_list);
  testing::internal::CaptureStdout();
  print_word_ladder(wordLadder1);
  string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output1, "Word ladder found: car cat chat cheat \n");

  vector<string> wordLadder2 = generate_word_ladder("party", "curls", word_list);
  testing::internal::CaptureStdout();
  print_word_ladder(wordLadder2);
  string output2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output2, "Word ladder found: party parts carts cards curds curls \n");
}

TEST(WordLadder, testGenerateWordLadder_word) {
  set<string> word_list;
  load_words(word_list, "src/words.txt");

  // EXPECT_EQ(generate_word_ladder("cat", "dog", word_list).size(), 4);
  // EXPECT_EQ(generate_word_ladder("marty", "curls", word_list).size(), 6);
  // EXPECT_EQ(generate_word_ladder("code", "data", word_list).size(), 6);
  // EXPECT_EQ(generate_word_ladder("work", "play", word_list).size(), 6);
  // EXPECT_EQ(generate_word_ladder("sleep", "awake", word_list).size(), 8);
  // EXPECT_EQ(generate_word_ladder("car", "cheat", word_list).size(), 4);
  // vector<string> ladder1 = generate_word_ladder("zoos", "sleep", word_list);
  // EXPECT_EQ(ladder1.size(), 8);
  // print_word_ladder(ladder1);
  // EXPECT_EQ(generate_word_ladder("were", "were", word_list).size(), 0);
}

TEST(Dijkstra, testDijkstraShortestPath) {
  Graph G;
  file_to_graph("src/small.txt", G);

  vector<int> previous(G.size(), -1);
  vector<int> distances = dijkstra_shortest_path(G, 0, previous);

  testing::internal::CaptureStdout();
  print_path(previous, previous.size());
  string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output1, "-1 3 1 0 \nTotal cost is 4\n");
}

TEST(Dijkstra, testExtractShortestPath) {
  Graph G;
  file_to_graph("src/large.txt", G);

  vector<int> previous(G.size(), -1);
  vector<int> distances = dijkstra_shortest_path(G, 0, previous);

  int destination = 6;
  vector<int> path1 = extract_shortest_path(distances, previous, destination);
  
  testing::internal::CaptureStdout();
  print_path(path1, path1.size());
  string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output1, "0 3 5 6 \nTotal cost is 4\n");

  EXPECT_EQ(distances[destination], 12);
}