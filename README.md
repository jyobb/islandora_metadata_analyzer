# Islandora Metadata Analyzer

Islandora module for inspecting collection metadata

## Introduction

This module allows administrators to analyze the metadata for a collection to find inconsistencies.  It aggregates the metadata for all items in a collection into a format that allows analysis.  It also allows users to download a CSV file of islandora PIDS for with metadata elements in common.  For example, all PIDS that have a specific subject.

## Requirement

This module requires the following modules/libraries

* [Islandora](https://github.com/islandora/islandora)
* [Tuque](https://github.com/islandora/tuque)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

N/A

## Documentation

Not yet complete

## Usage

Navigate to the collection analysis page using the link in the right navigation block. Here you can add:

1. A title for the search
2. Select a datastream to analyse
3. Add the PID of the collection being inspected
4. Select the fields to capture

##Status

Needs code comments
Currently does not look at books or subcollections.
Will work with MODS DC is next

