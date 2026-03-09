/* 
Citation for the following section of code
Date: 3/02/26
Code wrote by Project Group 35 (Greyson Sparling, Noah Letter) using code from canvas explorations as reference
Source URL: https://canvas.oregonstate.edu/courses/2031764/pages/exploration-web-application-technology-2?module_item_id=26243419
*/

const TableRow = ({ rowObject , actions}) => {
    return (
        <tr>
            {Object.values(rowObject).map((value, index) => (
                <td key={index}>{value}</td>
            ))}
            {actions && <td>{actions}</td>}
        </tr>
    );
};

export default TableRow;