# special-doodle
Структура телефонной книги состоит из двух unordered_map'ов (для быстрого поиска имени по телефону и наоборот) и из бора по номерам телефонов. Каждая вершина бора имеет поле, хранящее имена, до телефонов которых можно добраться через эту вершину (при добавлении чьего-то номера в бор будем добавлять имя человека в соответствующее поле каждой промежуточной вершины бора). Имена из телефонной книги хранятся отдельно в векторе, им соответствуют индексы в этом векторе. Чтобы не тратиться на имена целиком, в вершинах бора будем хранить позиции подходящих (до чьих номеров можно добраться) имен. 

(ALPHABET_SIZE нужно сделать 10, по инерции тыкнула 26)

Для выполнения дополнительного задания можно построить такие же боры для суффиксов номеров (11) и разбить номер со * на подномера, разделенные *. Для каждого подномера в соответствующем боре найти имена подходящих кандидатов.
