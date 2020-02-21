#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from flask import Flask, jsonify, request
import json
import os

cur_path = os.path.dirname(__file__)
color_file = os.path.join(cur_path, "colors.json")
with open(color_file, "r") as f:
    colors = json.load(f)

app = Flask(__name__)

@app.route("/colors", methods=["GET"])
def get_colors():
    return jsonify({ "data": colors })

@app.route("/colors/<name>", methods=["GET"])
def get_color(name):
    for color in colors:
        if color["name"] == name:
            return jsonify(color)
    return jsonify({ "error": True })


@app.route("/colors", methods=["pOST"])
def create_color():
    print("create_color")
    color = {
        "name": request.json["name"],
        "value": request.json["value"],
    }
    colors.append(color)
    return jsonify(color), 201

@app.route("/colors/<name>", methods=["PUT"])
def update_color(name):
    success = False
    for color in colors:
        if color["name"] == name:
            color["value"] = request.json.get("value", color["value"])
            return jsonify(color)
    return jsonify({ "error": True })

@app.route("/colors/<name>", methods=["DELETE"])
def delete_colors(name):
    success = False
    for color in colors:
        if color["name"] == name:
            colors.remove(color)
            return jsonify(color)
    return jsonify({ "error": True })


if __name__ == "__main__":
    app.run(debug=True)