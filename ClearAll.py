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

import shutil
import argparse
from os.path import isdir, exists

parser = argparse.ArgumentParser(description='Remove build folder')
parser.add_argument('--directory',
                    nargs=1,
                    type=str,
                    default='build',
                    help='directory to be removed')

args = parser.parse_args()

confirmance = input(
    'Do you realy want to remove all including database? (type yes/no) ')
directory = ''.join(args.directory)
if confirmance == 'yes':
    if exists(directory) and isdir(directory):
        shutil.rmtree(directory, ignore_errors=True)
        print('Cleared')
    else:
        print('Given parameter is not valid directory')
