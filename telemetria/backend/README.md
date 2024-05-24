# Backend em Nodejs

## Pre-requisites

- Install [Node.js](https://nodejs.org/en)

## Getting started

- Clone a [develop branch](https://github.com/MudRunnerBaja/Eletronica/tree/develop) do repositório - ou a branch mais adequada

- Instale as dependencias

```
cd Eletronica/telemetria/backend
npm install
```

- Construa e rode o projeto

```
npm run sdev
```

Endpoints podem ser visitados em `http://localhost:8001`

## Running the build

All the different build steps are orchestrated via [npm scripts](https://docs.npmjs.com/misc/scripts).
Npm scripts basically allow us to call (and chain) terminal commands via npm.

| Npm Script   | Description                                                                     |
| ------------ | ------------------------------------------------------------------------------- |
| `start`      | Runs full build and runs node on dist/index.js. Can be invoked with `npm start` |
| `build:copy` | copy the \*.yaml file to dist/ folder                                           |
| `build:live` | Full build. Runs ALL build tasks                                                |
| `build:dev`  | Full build. Runs ALL build tasks with all watch tasks                           |
| `dev`        | Runs full build before starting all watch tasks. Can be invoked with `npm dev`  |
| `test`       | Runs build and run tests using mocha                                            |
| `lint`       | Runs TSLint on project files                                                    |

## API Document endpoints

- TODO

## Variáveis e Ambiente

This project uses the following environment variables:

| Name | Description | Default Value |
| ---- | ----------- | ------------- |
|      |             |               |

