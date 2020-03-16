////////////////////////////////////////////////////////////////////////////////
// Authors: Vitor Bandeira, Eder Matheus Monteiro e Isadora
// Oliveira
//          (Advisor: Ricardo Reis)
//
// BSD 3-Clause License
//
// Copyright (c) 2019, Federal University of Rio Grande do Sul (UFRGS)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include "SteinerTree.h"

namespace FastRoute {

void SteinerTree::printSegments() {
	for (Segment seg : _segments) {
		std::cout << "(" << seg.getFirstNode().getPosition().getX() << ", " <<
			     seg.getFirstNode().getPosition().getY() << ", " <<
			     seg.getFirstNode().getLayer() << "); (" <<
			     seg.getLastNode().getPosition().getX() << ", " <<
			     seg.getLastNode().getPosition().getY() << ", " << 
			     seg.getLastNode().getLayer() << ")\n";
	}
}

void SteinerTree::addNode(Node node) {
        if (!nodeExists(node)) {
                _nodes.push_back(node);
	} else if(node.getType() == SOURCE) {
		for (Node &n : _nodes) {
			if (n == node) {
				n.setType(SOURCE);
			}
		}
	}
}

void SteinerTree::addSegment(Segment segment) {
        for (Segment seg : _segments) {
                if ((seg.getFirstNode() == segment.getFirstNode() &&
                     seg.getLastNode() == segment.getLastNode()) ||
                    (seg.getFirstNode() == segment.getLastNode() &&
                     seg.getLastNode() == segment.getFirstNode())) {
                       return;
                }
        }
        
        _segments.push_back(segment);
}

bool SteinerTree::nodeExists(Node node) {
        for (Node n : _nodes) {
                if (n == node) {
                        return true;
                }
        }
        return false;
}

bool SteinerTree::getNodeIfExists(Node node, Node &requestedNode) {
        for (Node n : _nodes) {
                if (n == node) {
                        requestedNode = n;
                        return true;
                }
        }
        
        return false;
}

std::vector<Segment> SteinerTree::getNodeSegments(Node node) {
        std::vector<Segment> nodeSegments;
        for (Segment seg : _segments) {
                if (seg.getFirstNode() == node || seg.getLastNode() == node) {
                        nodeSegments.push_back(seg);
                }
        }
        
        return nodeSegments;
}

Node SteinerTree::getSource() {
        Node source;
        bool found = false;
        for (Node node : _nodes) {
                if (node.getType() == SOURCE) {
                        source = node;
                        found = true;
                }
        }
        
        if (!found) {
                std::cout << "[ERROR] Source not found\n";
                std::exit(0);
        }
        
        return source;
}

std::vector<Node> SteinerTree::getSinks() {
        std::vector<Node> sinks;
        
        for (Node node : _nodes) {
                if (node.getType() == SINK) {
                        sinks.push_back(node);
                }
        }
        
        return sinks;
}

Segment SteinerTree::getSegmentByIndex(int index) {
        Segment idxSeg;
        for (Segment seg : _segments) {
                if (seg.getIndex() == index) {
                        idxSeg = seg;
                        break;
                }
        }
        
        return idxSeg;
}

}
