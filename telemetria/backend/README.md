# Nodejs Template

# Environment vars

This project uses the following environment variables:

| Name | Description | Default Value |
| ---- | ----------- | ------------- |
|      |             |               |

# Pre-requisites

- Install [Node.js](https://nodejs.org/en)

# Getting started

- Clone a [main branch](https://github.com/MudRunnerBaja/Eletronica) do repositório

- Instale as dependencias

```
cd Eletronica/telemetria/backend
npm install
```

- Build and run the project

```
npm run start:dev
```

Navigate to `http://localhost:8001`

- API Document endpoints

# TypeScript + Node

## Getting TypeScript

Add Typescript to project `npm`.

```

npm install -D typescript

```

## Building the project

### Configuring TypeScript compilation

```json
{
  "compilerOptions": {
    "target": "es5",
    "module": "commonjs",
    "outDir": "dist",
    "sourceMap": true
  },

  "include": ["src/**/*.ts"],
  "exclude": ["src/**/*.spec.ts", "test", "node_modules"]
}
```

### Running the build

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

# TSLint

TSLint is a code linter that helps catch minor code quality and style issues.

## TSLint rules

All rules are configured through `tslint.json`.

## Running TSLint

To run TSLint you can call the main build script or just the TSLint task.

```
npm run build:live   // runs full build including TSLint
npm run lint  // runs only TSLint
```

# Common Issues

## npm install fails

The current solution has an example for using a private npm repository. if you want to use the public npm repository, remove the .npmrc file.
