
#pragma once

#include <string>

class ScoreBoard {
private:

  static const char* c_score_file;

  typedef struct _S_SCORE {
    int   score;
    char  name[3];
    char  day;
    char  month;
    short year;
  } T_SCORE, *PT_SCORE;

  T_SCORE m_scores[10];

  int m_new_position;


public:

  ScoreBoard();

  void reset();
  void load();
  void save();

  std::string name_at(int);
  int score_at(int);
  void date_at( int, char*, int );

  bool is_on_high_scores(int);
  int loweset_score();

  void push_new_score(int);
  void set_new_name(char *);
  //void cancel_new_score();

  int new_score_pos();
  void clear_new_score_pos();
};

