all: get_dict python_dependencies
	+$(MAKE) -C src

get_dict:
	if [ ! -d './Wordlists-PT-BR' ] ; then git clone https://github.com/mauricioomateus/Wordlists-PT-BR.git ; fi

python_dependencies:
	python3 -m venv venv
	./venv/bin/python3 -m pip install -U --upgrade pip
	./venv/bin/python3 -m pip install -U numpy

