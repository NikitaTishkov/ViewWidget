/**
 *An API KEY required for connection to google api`s
 */
#define API_KEY "AIzaSyBgxTSi0WNEyNNN7JyuimLMgk9XMGT2bjI"
/** This function make a simple http request with GET method on Youtube Data API
 * External library curl
 */
/**
 * Request maker
 *
 * :param id: An id of video from which user is going to get data about
 * :return: Return 0 if all methods in function done successfull
 *
 * This function make a simple http request with GET method on Youtube Data API
 * External library curl
 * As a result GetFromApi creates or rewrite temp.json with data
 */
int GetFromApi(const char* id);
