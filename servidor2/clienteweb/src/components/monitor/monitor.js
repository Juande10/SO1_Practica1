import React, { Component } from 'react';
import {Row, Col } from 'react-bootstrap';
import CPU from '../cpu/cpu.js'
import RAM from '../ram/ram.js'


class Monitor extends Component {
    constructor(props) {
        super(props);
        this.state = {url : this.props.URL };
    }

    render() {
        return (
            <Row>
                <Col md={6}>
                    <CPU URL={this.state.url}></CPU>
                </Col>
                <Col md={6}>
                    <RAM URL={this.state.url}></RAM>
                </Col>
            </Row>
        );
    }
    
}

export default Monitor;