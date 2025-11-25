import { useNavigate } from 'react-router-dom';
import './Cover.css';

function Cover() {
  const navigate = useNavigate();

  return (
    <div className="cover-page">
      <div className="cover-content">
        <h1 className="cover-title">YOUR REFRIGERATOR</h1>

        <div className="cover-buttons">
          <button
            className="cover-button inventory-button"
            onClick={() => navigate('/inventory')}
          >
            INVENTORY
          </button>

          <button
            className="cover-button meal-ideas-button"
            onClick={() => navigate('/meal-ideas')}
          >
            MEAL IDEAS
          </button>

          <button
            className="cover-button scan-receipt-button"
            onClick={() => navigate('/scan-receipt')}
          >
            SCAN RECEIPT
          </button>
        </div>
      </div>
    </div>
  );
}

export default Cover;
