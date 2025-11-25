import { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import axios from 'axios';
import './Inventory.css';

function Inventory() {
  const navigate = useNavigate();
  const [ingredients, setIngredients] = useState([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    fetchIngredients();
  }, []);

  const fetchIngredients = async () => {
    try {
      const response = await axios.get('http://localhost:3001/api/ingredients');
      setIngredients(response.data);
      setLoading(false);
    } catch (error) {
      console.error('Error fetching ingredients:', error);
      setLoading(false);
    }
  };

  const calculateDaysUntilExpiry = (expiryDate) => {
    const today = new Date();
    const expiry = new Date(expiryDate);
    const diffTime = expiry - today;
    const diffDays = Math.ceil(diffTime / (1000 * 60 * 60 * 24));

    if (diffDays < 0) return 'expired';
    if (diffDays === 0) return 'today';
    if (diffDays === 1) return '1 day';
    return `${diffDays} days`;
  };

  return (
    <div className="inventory-page">
      <div className="page-header">
        <h1 className="page-title">INVENTORY</h1>
      </div>

      <div className="inventory-content">
        {loading ? (
          <p>Loading ingredients...</p>
        ) : ingredients.length === 0 ? (
          <p className="empty-message">No ingredients in your fridge yet!</p>
        ) : (
          <table className="inventory-table">
            <thead>
              <tr>
                <th>Vegetable/Item</th>
                <th>No.</th>
                <th>Expires</th>
              </tr>
            </thead>
            <tbody>
              {ingredients.map((ingredient) => (
                <tr key={ingredient.id}>
                  <td>{ingredient.name}</td>
                  <td>{ingredient.quantity}</td>
                  <td className={calculateDaysUntilExpiry(ingredient.expiry_date) === 'expired' ? 'expired' : ''}>
                    {calculateDaysUntilExpiry(ingredient.expiry_date)}
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        )}
      </div>

      <div className="navigation-bar">
        <button className="nav-button home" onClick={() => navigate('/')}>
          <svg width="24" height="24" viewBox="0 0 24 24" fill="currentColor">
            <path d="M10 20v-6h4v6h5v-8h3L12 3 2 12h3v8z"/>
          </svg>
        </button>
        <button className="nav-button back" onClick={() => navigate(-1)}>
          <svg width="24" height="24" viewBox="0 0 24 24" fill="currentColor">
            <path d="M20 11H7.83l5.59-5.59L12 4l-8 8 8 8 1.41-1.41L7.83 13H20v-2z"/>
          </svg>
        </button>
      </div>
    </div>
  );
}

export default Inventory;
