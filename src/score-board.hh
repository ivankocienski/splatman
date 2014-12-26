
#pragma once

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

  const char* name_at(int);
  int score_at(int);
  void date_at( int, char*, int );

  bool is_on_high_scores(int);

  void push_new_score(int);
  void set_new_name(char *);
  //void cancel_new_score();
};

