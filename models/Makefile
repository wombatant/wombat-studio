all: models liccor
models:
	cat defs/models.cy editormodels.cy > models.cy
	cyborgbear -i models.cy -o generated -n models -t cpp-qt
	rm -f models.cy
liccor:
	liccor
clean:
	rm -f models.cy models.[c,h]pp
