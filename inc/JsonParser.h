/**
 * Taking certain data
 *
 * :param target: number from 0 to 3 that indicates which of the following
 *  value will executed: [views, likes, dislikes, comments]
 * :return: Returns integer value contains number of views, likes, dislikes or
 * comments
 *
 * This function use json-c lib for taking data from temp.json
 */
int GetFromJSON_statistics(int target);
