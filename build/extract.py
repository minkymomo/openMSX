# $Id$
# Extract files from archives.

from os import O_CREAT, O_WRONLY, fdopen, mkdir, open as osopen
from os.path import abspath, isdir, join as joinpath, sep, split as splitpath
from stat import S_IRWXU, S_IRWXG, S_IRWXO, S_IXUSR, S_IXGRP, S_IXOTH
import sys
import tarfile

# Note: Larger buffers might make extraction slower.
bufSize = 16384

def extract(archivePath, destDir, rename = None):
	'''Extract the given archive to the given directory.
	If a rename function is given, it is called with the output path relative
	to the destination directory; the value returned by the rename function is
	used as the actual relative destination file path.
	This function sets file ownership and permissions like is done in newly
	created files and ignores the ownership and permissions from the archive,
	since we are not restoring a backup.
	'''
	absDestDir = abspath(destDir) + sep
	if not isdir(absDestDir):
		raise ValueError(
			'Destination directory "%s" does not exist' % absDestDir
			)

	tar = tarfile.open(archivePath)
	# Note: According to the Python 2.6 docs, errorlevel can be passed as a
	#       keyword argument to the open() call, but on Python 2.5 this does
	#       not work.
	tar.errorlevel = 2

	try:
		for member in tar.getmembers():
			absMemberPath = abspath(joinpath(absDestDir, member.name))
			if member.isdir():
				absMemberPath += sep
			if not absMemberPath.startswith(absDestDir):
				raise ValueError(
					'Refusing to extract tar entry "%s" '
					'outside destination directory'
					% member.name
					)
			if rename:
				absMemberPath = absDestDir + rename(
					absMemberPath[len(absDestDir) : ]
					)

			if member.isfile():
				mode = S_IRWXU | S_IRWXG | S_IRWXO
				if not (member.mode & S_IXUSR):
					mode &= ~(S_IXUSR | S_IXGRP | S_IXOTH)
				out = fdopen(
					osopen(absMemberPath, O_CREAT | O_WRONLY, mode),
					'wb'
					)
				try:
					inp = tar.extractfile(member)
					bytesLeft = member.size
					while bytesLeft > 0:
						buf = inp.read(bufSize)
						out.write(buf)
						bytesLeft -= len(buf)
					buf = None
				finally:
					out.close()
			elif member.isdir():
				if not isdir(absMemberPath):
					mkdir(absMemberPath)
			else:
				raise ValueError(
					'Cannot extract tar entry "%s": '
					'not a regular file or a directory'
					% member.name
					)
	finally:
		tar.close()

if 3 <= len(sys.argv) <= 4:
	if len(sys.argv) == 4:
		newName = sys.argv[3]
		def renameTopLevelDir(oldPath):
			head, tail = splitpath(oldPath)
			headParts = head.split(sep)
			if not headParts:
				raise ValueError(
					'Directory part is empty for entry "%s"' % oldPath
					)
			headParts[0] = newName
			return sep.join(headParts + [ tail ])
	else:
		renameTopLevelDir = None
	extract(sys.argv[1], sys.argv[2], renameTopLevelDir)
else:
	print >>sys.stderr, \
		'Usage: python extract.py archive destination [new-top-level-dir]'
	sys.exit(2)