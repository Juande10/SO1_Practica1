import React, { Component } from 'react';
import axios from 'axios';

class DataMonitor extends Component {
    constructor(props) {
        super(props);
    }

    componentDidMount() {
        this.interval = setInterval(() => {
            axios.get(this.props.URL + `/getData`)
            .then(res => {
                console.log(res);
            })
        }, 5000)
    }

    render() {
        return(
            <h2>Hola</h2>
        );
    }
}

export default DataMonitor;