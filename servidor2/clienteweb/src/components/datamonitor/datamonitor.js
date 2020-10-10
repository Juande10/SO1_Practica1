import React, { Component } from 'react';
import axios from 'axios';
import TableScrollbar from 'react-table-scrollbar';
import { Col, Row } from 'react-bootstrap';

class DataMonitor extends Component {
    constructor(props) {
        super(props);
        this.state = {data : []}
    }

    componentDidMount() {
        this.interval = setInterval(() => {
            axios.get(this.props.URL + `/getData`)
            .then(res => {
                console.log(res['data'].data);
                console.log(JSON.parse(res['data'].data));
                this.setState({data:JSON.parse(res['data'].data)});
            })
        }, 5000)
    }

    componentWillUnmount() {
        clearInterval(this.interval);
    }

    render() {
        return(
            <Row className="pre-scrollable">
                {this.state.data.map(this.renderNote)}
            </Row>
        );
    }

    renderNote(note, index) {
        return (
            <Col key={index} md={4} className="d-flex justify-content-center">
                <div className="card text-white bg-primary m-3" style={{maxWidth: '18rem'}}>
                    <div className="card-header">{note.autor}</div>
                    <div className="card-body">
                        <p className="card-text">{note.nota}</p>
                    </div>
                </div>
            </Col>
        )
    }
}

export default DataMonitor;