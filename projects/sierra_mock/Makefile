SHELL = /bin/sh
.DEFAULT_GOAL := help
.PHONY: init build tests clean

all: ## Run the build task.
all: build

init: ## Setup your local env, e.g. create virtual env with dependancies installed.
	@echo "Create your secrets file under Sierra_50."

build: ## Build whatever your project is, e.g. docker build for a local image.
	docker image build --squash -t molecule-iii  .

test: ## Run any tests.
	@echo "There are no tests yet."

clean: ## Purge generated files which are not needed. e.g. *.retry file in ansbile.
	@echo "Nothing to do yet."

help: ## Show this help
	@awk 'BEGIN {FS = ":.*?## "} /^[0-9a-zA-Z_-]+:.*?## / {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)