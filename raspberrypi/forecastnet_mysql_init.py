import mysql.connector

mydb = mysql.connector.connect(
  host="localhost",
  user="yourusername", # CHANGE THIS!
  password="yourpassword" # CHANGE THIS!
)

mycursor = mydb.cursor()

print(mydb)