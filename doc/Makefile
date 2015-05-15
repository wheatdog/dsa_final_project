# Produce PDFs from all Markdown files in a directory
# Lincoln Mullen | http://lincolnmullen.com | lincoln@lincolnmullen.com

# List files to be made by finding all *.md files and appending .pdf
PDFS := $(patsubst %.tex,%.tex.pdf,$(wildcard *.tex))

# The all rule makes all the PDF files listed
all : $(PDFS)
                        
# This generic rule accepts PDF targets with corresponding Markdown 
# source, and makes them using pandoc
# NOTE(wheatdog): Remove temporary directories on windows
%.tex.pdf : %.tex
	rubber -v --pdf $<
	mv $(patsubst %.tex,%.pdf,$<) $@
	rubber --clean $<

# Remove all PDF outputs
clean :
	rm $(PDFS)

# Remove all PDF outputs then build them again
rebuild : clean all

upload:
	scp -r ../../hw2/ b03902028@linux7.csie.ntu.edu.tw:dsa/
