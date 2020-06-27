#!/usr/bin/env python3

import sys,os,re,glob

class ParseCSV(object):

    def __init__(self, csv_name):
        self.name = ""
        self.rows = []
        self.columns = ""
        self.json = ""

        self.row_idx = 0
        self.col_idx = 0

        self.name = csv_name
        rows = open(self.name, 'r')
        self.rows = rows.read().split('\n')
        rows.close()

        self.columns = self.rows[0].split(',')
        
        self.start_json()
        self.parse_rows()
        self.end_json()

    def input_key(self):
        return '\n' + " "*12 + '"' + self.columns[self.col_idx] + "\": "

    def input_value(self, col):
        try:
            int(col)
            value = col
        except:
            value = '"' + col + '"'
        return str(value) + ","

    def parse_rows(self):
        self.row_idx = 0
        for row in self.rows[1:]:
            if len(row) < 2:
                continue
            self.json += "\n        {" # start new object
            self.col_idx = 0
            for col in row.split(','): # split object up by values
                self.json += self.input_key() + self.input_value(col) # add key value pairs
                self.col_idx += 1
            self.json = self.json[0:-1] # trim the final ','
            self.json += "\n        }," # close the object
            self.row_idx += 1
        self.json = self.json[0:-1] # remove the final ','
    

    def start_json(self):
        self.json = """
{ "Rows" : 
    [
"""
    def end_json(self):
        self.json += """
    ]
}
        """

    def __str__(self):
        return self.json


def main():
    csv_lst = sys.argv[1:]
    if csv_lst[0][-1][0] == '*': # if we want a glob
        csv_lst = glob.glob(csv_lst[0])

    for data in csv_lst:
        csv = ParseCSV(data)
        print("Parsing CSV: " + csv.name)
        print(csv)

        try:
            os.mkdir("./json", 766) 
        except:
            True

        file = open("./json/" + re.sub(r'^.+[\\/]|\.[^\.]*$', '', csv.name)+".json", 'w')
        file.write(csv.json)
        file.close()



if __name__ == "__main__": # ensure this is running directly instead of as a module.
    main()





