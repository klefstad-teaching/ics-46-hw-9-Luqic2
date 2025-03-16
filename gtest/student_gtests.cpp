#include <gtest/gtest.h>

#include "../src/dijkstras.h"
#include "../src/ladder.h"

TEST(v, testLoadWords) {
  set<string> word_list;
  load_words(word_list, "src/shortWords.txt");

  testing::internal::CaptureStdout();
  for (auto word : word_list) {
      cout << word << " ";
  }
  string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "bear car cat chair chat cheat hair hear ");
}

TEST(WordLadder, testEditDistanceWithin) {
  EXPECT_TRUE(edit_distance_within("bear", "hear", 1));

  EXPECT_TRUE(edit_distance_within("chair", "hair", 1));

  EXPECT_TRUE(edit_distance_within("cheat", "chat", 1));

  EXPECT_TRUE(edit_distance_within("car", "care", 1));
}


// TEST(WordLadder, testGenerateWordLadder) {
  
// }
