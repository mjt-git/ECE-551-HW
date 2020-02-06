#include "election.h"

#include <stdio.h>

#include "string.h"
//include any other headers you need here...

int findSemicolomIdx(int start, int totalLen, const char * line) {
  int semicolom = 0;
  int flag = 0;  // is 1 if there is n semicolom
  for (int i = start; i < totalLen; i++) {
    if (line[i] == '\n') {  // check if there is \n in the line
      fprintf(stderr, "There is a \n in the line");
      exit(EXIT_FAILURE);
    }
    if (line[i] == ':') {
      semicolom = i;
      flag = 1;
      break;
    }
  }
  if (flag == 0) {
    fprintf(stderr, "There is no semicolom between %d to the end of line", start);
    exit(EXIT_FAILURE);
  }
  return semicolom;
}

void checkDigit(char ch) {  // check if ch is digit
  if (ch < '0' || ch > '9') {
    fprintf(stderr, "certain character is not a digit");
    exit(EXIT_FAILURE);
  }
}

state_t parseLine(const char * line) {
  // calculate the totalLen of line
  if (line == NULL) {
    fprintf(stderr, "The line is NULL");
    exit(EXIT_FAILURE);
  }
  int totalLen = 0;
  while (line[totalLen] != '\0') {
    totalLen++;
  }
  // find the index of first :
  int semicolom1 = findSemicolomIdx(0, totalLen, line);
  // find the index of semicolom2
  int semicolom2 = findSemicolomIdx(semicolom1 + 1, totalLen, line);
  // check the format of line
  if (semicolom2 == 0) {
    fprintf(stderr, "There is no second semicolom");
    exit(EXIT_FAILURE);
  }
  if (semicolom2 - semicolom1 == 1) {
    fprintf(stderr, "There is nothing between second semicolom and first semicolom");
    exit(EXIT_FAILURE);
  }
  // construct string of state name

  int nameLen = semicolom1;
  char stateName[nameLen + 1];
  for (int j = 0; j < nameLen; j++) {
    stateName[j] = line[j];
  }
  stateName[nameLen] = '\0';

  // construct string of pop
  int popLen = semicolom2 - semicolom1 - 1;
  char pop[popLen + 1];
  for (int j = 0; j < popLen; j++) {
    char ch1 = line[semicolom1 + 1 + j];
    checkDigit(ch1);
    pop[j] = ch1;
  }
  pop[popLen] = '\0';
  // construct string of voteNum
  int voteLen = totalLen - semicolom2 - 1;
  char voteNum[voteLen + 1];
  for (int k = 0; k < voteLen; k++) {
    char ch = line[semicolom2 + 1 + k];
    checkDigit(ch);
    voteNum[k] = ch;
  }
  voteNum[voteLen] = '\0';
  //construct state_t
  state_t state;
  for (int i = 0; i < nameLen; i++) {
    state.name[i] = stateName[i];
  }
  state.name[nameLen] = '\0';
  uint64_t popNum = atoi(pop);
  state.population = popNum;
  unsigned int elecVote = atoi(voteNum);
  state.electoralVotes = elecVote;
  return state;
}

int winAll(uint64_t pop, uint64_t voteA) {  // return 1 if vote for A strictly over 50%
  if (voteA * 2 > pop) {
    return 1;
  }
  return 0;
}

unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  unsigned int total = 0;  // total is the total number of votes A received
  for (size_t i = 0; i < nStates; i++) {
    if (winAll(stateData[i].population, voteCounts[i]) == 1) {
      total += stateData[i].electoralVotes;
    }
  }
  return total;
}

double absD(double d) {  // calculate absolute value of double
  if (d > 0) {
    return d;
  }
  return -1 * d;
}

double needRecount(
    uint64_t pop,
    uint64_t voteA) {  // return the actual percentage if recount needed, otherwise 0.0
  double popD = (double)pop;
  double voteAD = (double)voteA;
  double res = voteAD / popD;
  if (absD(res - 0.5) <= 0.005) {
    return res;
  }
  return 0.0;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  for (size_t i = 0; i < nStates; i++) {
    double res = needRecount(stateData[i].population, voteCounts[i]);
    if (res > 0) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             res * 100);
    }
  }
}

double calcD(uint64_t pop,
             uint64_t voteA) {  // return the percentage of vote for A in pop
  double popD = (double)pop;
  double voteAD = (double)voteA;
  double res = voteAD / popD;
  return res;
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  double max = 0;
  size_t idxMax = 0;
  for (size_t i = 0; i < nStates; i++) {
    double res = calcD(stateData[i].population, voteCounts[i]);
    if (res > max) {
      max = res;
      idxMax = i;
    }
  }
  printf(
      "Candidate A won %s with %.2f%% of the vote\n", stateData[idxMax].name, max * 100);
}
