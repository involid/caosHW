extern void normalize_path(char *path) {
  int curr_normilized = 0;
  int curr = 0;
  while (*(path + curr) != '\0') {
    if (*(path + curr) == '/') {
      if (curr_normilized > 0 && *(path + curr_normilized - 1) == '/') {
        ++curr;
      } else {
        *(path + curr_normilized) = *(path + curr);
        ++curr;
        ++curr_normilized;
      }
    } else if (*(path + curr) == '.') {
      if (curr_normilized > 0 && *(path + curr_normilized - 1) == '/') {
        if (*(path + curr + 1) == '/' || *(path + curr + 1) == '\0') {
          ++curr;
        } else if (*(path + curr + 1) == '.' &&
                   (*(path + curr + 2) == '/' || *(path + curr + 2) == '\0')) {
          curr += 2;
          --curr_normilized;
          while (curr_normilized > 0 && *(path + curr_normilized - 1) != '/') {
            --curr_normilized;
          }
        } else {
          *(path + curr_normilized) = *(path + curr);
          ++curr;
          ++curr_normilized;
        }
      } else {
        *(path + curr_normilized) = *(path + curr);
        ++curr;
        ++curr_normilized;
      }
    } else {
      *(path + curr_normilized) = *(path + curr);
      ++curr;
      ++curr_normilized;
    }
  }

  for (int i = curr; i >= curr_normilized; --i) {
    *(path + i) = '\0';
  }
}
