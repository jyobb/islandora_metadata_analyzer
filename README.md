# Islandora Metadata Analyzer

Islandora module for inspecting collection metadata

## Introduction

This module allows administrators to analyze MODS or DC metadata for a collection to find inconsistencies.  It aggregates the metadata for all items in a collection into a format that allows analysis. All unique paths within a metadata stream are displayed with links to to either view or download the list of pids in the collection that have or do not have this element. This allows you to check whether all metadata records have specific fields.

This module also allows you to capture the contents of a top level xml element and its children.  This is useful for ensuring consistency of your metadata. A CSV list of pids for each metadata value is viewable or downloadable so you can find objects that need repair. 


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

Currently does not look at books or subcollections.


