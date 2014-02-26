import MySQLdb

db = MySQLdb.connect("localhost", "root", "123_abc*#qt", "make10k")

cursor = db.cursor()

#cursor.execute("DROP TABLE make10k_index;")
cursor.execute("CREATE TABLE make10k_index("
        "id int(4) NOT NULL, name char(10) NOT NULL, PRIMARY KEY (id)"
    ") ENGINE=InnoDB DEFAULT CHARSET=utf8;")

for i in range(0, 1000):
    ss = "INSERT INTO make10k_index(id, name) VALUES"

    for j in range(0, 10000):
        ss += ( "('" + str(i*10000 + j) + "', 'n" + str(i*10000 + j) + "'),\n")

    ss = ss[:-2]
    ss += ";"

    cursor.execute(ss)
    db.commit()
    print "execute " + str(i*10000 + j) + " finished!\n"

