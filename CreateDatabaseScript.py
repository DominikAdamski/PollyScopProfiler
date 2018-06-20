#Polly Scop Profiler Runtime
#Copyright (C) 2018  Dominik Adamski

#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#any later version.

#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.

import sqlite3
import argparse
import contextlib

from os import mkdir
from os import errno
from os.path import exists, isdir, join


def create_output_directory(
        directory_name='str,len(directory_name)>0') -> 'None':
    """This function creates an output directory."""
    if exists(directory_name):
        if isdir(directory_name):
            return None
        else:
            raise OSError(errno.EEXIST, 'File exists', directory_name)
    mkdir(directory_name)
    return None


parser = argparse.ArgumentParser(
    description='Create new database for profiler of the scops')
parser.add_argument('--output-directory',
                    nargs=1,
                    type=str,
                    default='build',
                    help='output directory')
parser.add_argument('--database-name',
                    nargs=1,
                    type=str,
                    default='scops.db',
                    help='database name')

args = parser.parse_args()

build_dir = ''.join(args.output_directory)
database_name = ''.join(args.database_name)
database_path = join(build_dir, database_name)

try:
    create_output_directory(build_dir)
except BaseException:
    print('Invalid output directory')
    exit(1)

if exists(database_path):
    exit(0)

with contextlib.closing(sqlite3.connect(database_path)) as con:
    with con as cur:
        try:
            cur.execute('CREATE TABLE general_info (\
            id INTEGER PRIMARY KEY,\
            hash INTEGER,\
            name TEXT);')
            cur.execute('CREATE TABLE scop_info (\
            scop_id BLOB PRIMARY KEY,\
            general_info_id INTEGER,\
            max_loop_depth INTEGER,\
            instruction_number INTEGER,\
            sum_of_array_coeff INTEGER,\
            sum_of_array_offset INTEGER,\
            FOREIGN KEY (general_info_id) REFERENCES general_info (id)\
            ON  DELETE NO ACTION ON UPDATE NO ACTION);')
            cur.execute('CREATE TABLE loops(\
            scop_id BLOB,\
            range INTEGER,\
            loop_id INTEGER PRIMARY KEY,\
            FOREIGN KEY (scop_id) REFERENCES scop_info (scop_id));')
        except sqlite3.Error as e:
            print('Cannot set up database ' + str(e))