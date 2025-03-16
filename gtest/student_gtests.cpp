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
}

TEST(WordLadder, testGenerateWordLadder_shortWords) {
  set<string> word_list;
  load_words(word_list, "src/shortWords.txt");

  vector<string> wordLadder1 = generate_word_ladder("car", "cheat", word_list);
  testing::internal::CaptureStdout();
  print_word_ladder(wordLadder1);
  string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output1, "car -> cat -> chat -> cheat -> ");

  vector<string> wordLadder2 = generate_word_ladder("party", "curls", word_list);
  testing::internal::CaptureStdout();
  print_word_ladder(wordLadder2);
  string output2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output2, "party -> parts -> carts -> cards -> curds -> curls -> ");
}

TEST(WordLadder, testGenerateWordLadder_word) {
  set<string> word_list;
  load_words(word_list, "src/words.txt");

  EXPECT_EQ(generate_word_ladder("cat", "dog", word_list).size(), 4);
  EXPECT_EQ(generate_word_ladder("marty", "curls", word_list).size(), 6);
  EXPECT_EQ(generate_word_ladder("code", "data", word_list).size(), 6);
  EXPECT_EQ(generate_word_ladder("work", "play", word_list).size(), 6);
  EXPECT_EQ(generate_word_ladder("sleep", "awake", word_list).size(), 8);
  EXPECT_EQ(generate_word_ladder("car", "cheat", word_list).size(), 4);
}
